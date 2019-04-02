const globalVars = {
  print: console.log,
}

function Environment(parent) {
  this.vars = Object.create(parent ? parent.vars : null)
  if (parent) {
    this.parent = parent
  }
}

Environment.prototype = {
  extend: function() {
    return new Environment(this)
  },
  lookup: function(name) {
    let scope = this
    while (scope) {
      if (Object.prototype.hasOwnProperty.call(scope.vars, name)) {
        return scope
      }
      scope = scope.parent
    }
  },
  get: function(name) {
    if (name in this.vars) {
      return this.vars[name]
      // TODO: refactor
    } else if (this.parent && name in this.parent.vars) {
      return this.parent.vars[name]
    } else if (name in globalVars) {
      return globalVars[name]
    }
    throw new Error("Undefined variable " + name)
  },
  set: function(name, value) {
    const scope = this.lookup(name)
    if (!scope && this.parent) {
      throw new Error("Undefined variable " + name)
    }
    return (scope || this).vars[name] = value
  },
  def: function(name, value) {
    return this.vars[name] = value
  },
}

const expTypes = {
  assign: 'assignExpression',                 // =
  objLiteral: 'objLiteral',                   // []
  literalAssign: 'literalAssignExpression',   // : inside objLiteral
  member: 'memberExpression',                 // ->
  cond: 'ifStatement',                        // if
  binary: 'binaryExpression',                 // +, -, /, *, >, <
  loop: 'forEachStatement',                   // forEach,
  loopVar: 'identifierExpression',            // as
}

const varTypes = [
  'testVar',
  'questionVar',
  'var' // member var for objLiteral
]

function evaluate(exp, env) {
  switch (exp.type) {
    case 'num':
    case 'str':
    case 'bool':
      return exp.value

    case 'var':
      return env.get(exp.value)

    case 'testVar':
      return env.get(exp.name)

    case expTypes.assign: {
      if (!varTypes.includes(exp.left.type)) {
        throw new Error('Cannot assign to ' + JSON.stringify(exp.left))
      }

      const value = evaluate(exp.right, env)
      const varType = exp.left.type
      const varName = exp.left.name
      if (varType === 'testVar') {
        value.questions = {
          items: [],
          add: (newQuestion) => {
            value.questions.items.push(newQuestion)
          },
          remove: (wasteQuestion) => {
            value.questions.items = value.questions.items.filter((item) => (
              item.description !== wasteQuestion.description
            ))
          },
          get amount() {
            return value.questions.items.length
          }
        }
        value.answers = {
          items: [],
          add: (newQuestion) => {
            value.answers.items.push(newQuestion)
          },
          remove: (wasteQuestion) => {
            value.answers.items = value.answers.items.filter((item) => (
              item.id !== wasteQuestion.id
            ))
          },
          get amount() {
            return value.answers.items.length
          }
        }
      }
      return env.set(varName, value)
    }

    case expTypes.objLiteral: {
      const innerValues = {}
      exp.properties.forEach((literalAssignExp) => {
        const [key, value] = evaluate(literalAssignExp, env)
        innerValues[key] = value
      })
      return innerValues
    }

    case expTypes.literalAssign: {
      if (
        !exp.left ||
        !varTypes.includes(exp.left.type)
      ) {
        console.log('exp', exp)
        throw new Error('Cannot assign to ' + JSON.stringify(exp.left))
      }

      const key = exp.left.value
      const value = evaluate(exp.right, env)
      return [key, value]
    }

    case expTypes.member: {
      // get all members values of the literal
      const parent = evaluate(exp.left, env)
      // const localEnv = {
      //   vars: {
      //     ...parent,
      //   },
      // }
      // create a new env that consist only from parent members
      const innerEnv = new Environment(env)
      innerEnv.vars = {
        ...parent,
      }
      // call child on a closed env

      // let child
      // if (exp.right.type === 'call') {
      //   child = evaluate(exp.right, globalEnv)
      // } else {
      const child = evaluate(exp.right, innerEnv)
      // }
      
      return child
    }

    case expTypes.binary: {
      return applyOp(
        exp.operator,
        evaluate(exp.left, env),
        evaluate(exp.right, env)
      )
    }
      
    // case "lambda":
    //   return make_lambda(env, exp);

    case expTypes.cond: {
      const cond = evaluate(exp.cond, env)
      if (cond) {
        return evaluate(exp.then, env)
      } else if (exp.else) {
        return evaluate(exp.else, env)
      } else {
        return false
      }
    }

    case expTypes.loop: {
      const [varName, varValues] = evaluate(exp.inner, env)
      varValues.forEach((varValue) => {
        // create a new env that consist only from parent members
        const innerEnv = new Environment(env)
        innerEnv.vars = {
          [varName]: varValue,
        }
        const result = evaluate(exp.body, innerEnv)
      })
      return
    }

    case expTypes.loopVar: {
      const value = evaluate(exp.left, env)
      const varName = exp.right.value
      return [varName, value]
    }

    case "prog":
      let val = false
      exp.prog.forEach(function(exp) {
        val = evaluate(exp, env)
      })
      return val

    case 'call': {
      var func = evaluate(exp.func, env)
      return func.apply(null, exp.args.map((arg) => {
        return evaluate(arg, env)
      }))
    }

    default: {
      console.log('env', env)
      throw new Error("I don't know how to evaluate " + exp.type)
    }
  }
}

function applyOp(op, a, b) {
  const num = (x) => {
    if (typeof x !== 'number') {
      throw new Error('Expected number but got ' + x)
    }
    return x
  }

  switch (op) {
    case '+': return num(a) + num(b)
    case '-': return num(a) - num(b)
    case '*': return num(a) * num(b)
    case '/': return num(a) / num(b)
    case '%': return num(a) % num(b)
    case '&&': return a !== false && b
    case '||': return a !== false ? a : b
    case '<': return num(a) < num(b)
    case '>': return num(a) > num(b)
    case '<=': return num(a) <= num(b)
    case '>=': return num(a) >= num(b)
    case '==': return a === b
    case '!=': return a !== b
  }
  throw new Error('Can\'t apply operator ' + op)
}

// function make_lambda(env, exp) {
//   function lambda() {
//       var names = exp.vars;
//       var scope = env.extend();
//       for (var i = 0; i < names.length; ++i)
//           scope.def(names[i], i < arguments.length ? arguments[i] : false);
//       return evaluate(exp.body, scope);
//   }
//   return lambda;
// }




// /* -----[ entry point for NodeJS ]----- */

// var globalEnv = new Environment();



// globalEnv.def("time", function(func){
//   try {
//       console.time("time");
//       return func();
//   } finally {
//       console.timeEnd("time");
//   }
// });

// if (typeof process != "undefined") (function(){
//   var util = require("util");
//   globalEnv.def("println", function(val){
//       util.puts(val);
//   });
//   globalEnv.def("print", function(val){
//       util.print(val);
//   });
//   var code = "";
//   process.stdin.setEncoding("utf8");
//   process.stdin.on("readable", function(){
//       var chunk = process.stdin.read();
//       if (chunk) code += chunk;
//   });
//   process.stdin.on("end", function(){
//       var ast = parse(TokenStream(InputStream(code)));
//       evaluate(ast, globalEnv);
//   });
// })();