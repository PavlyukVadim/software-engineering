function InputStream(input) {
  let pos = 0, line = 1, col = 0
  
  const next = () => {
    const ch = input.charAt(pos++)
    if (ch === '\n') {
      line++
      col = 0
    } else {
      col++
    }
    return ch
  }

  const peek = () => input.charAt(pos)

  const eof = () => (peek() === '')

  const croak = (msg) => {
    throw new Error(msg + ' (' + line + ':' + col + ')')
  }

  return {
    next,
    peek,
    eof,
    croak,
  }
}

// TokenStream function
function TokenStream(input) {
  let current = null
  
  const keywords = [
    'test',     // type of var, consist of questions
    'question', // type of var, part of test
    'if',       // cond statement
    'else',     // cond statement
    'forEach',  // loof
    'as',       // variable declaration inside forEach
    'true',     // bool value
    'false',    // bool value
  ]

  const isKeyword = (x) => keywords.includes(x)

  const isDigit = (ch) => /[\d]/i.test(ch)

  const isIdStart = (ch) => /[\w]/i.test(ch)

  const isId = (ch) => (isIdStart(ch) || '0123456789'.includes(ch))
  
  const isOpChar = (ch) => '+-*/%=:&|<>!'.includes(ch)

  const isPunc = (ch) => ',;(){}[]'.includes(ch)

  const isWhitespace = (ch) => ' \t\n'.includes(ch)

  const readWhile = (predicate) => {
    let str = ''
    while (!input.eof() && predicate(input.peek())) {
      str += input.next()
    }
    return str
  }

  const readNumber = () => {
    let hasDot = false
    const number = readWhile(function(ch) {
      if (ch === '.') {
        if (hasDot) return false
        hasDot = true
        return true
      }
      return isDigit(ch)
    })

    return {
      type: 'num',
      value: parseFloat(number),
    }
  }

  const readIdent = () => {
    const id = readWhile(isId)

    return {
      type: isKeyword(id) ? 'kw' : 'var',
      value: id,
    }
  }

  const readEscaped = (end) => {
    let escaped = false, str = ''
    input.next()
    while (!input.eof()) {
      let ch = input.next()
      if (escaped) {
        str += ch
        escaped = false
      } else if (ch == "\\") {
        escaped = true
      } else if (ch == end) {
        break
      } else {
        str += ch
      }
    }
    return str
  }

  const readString = () => {
    return {
      type: 'str',
      value: readEscaped('"'),
    }
  }

  const skipComment = () => {
    readWhile(function(ch) { return ch !== '\n' })
    input.next()
  }

  const readNext = () => {
    // read to first char
    readWhile(isWhitespace)
    if (input.eof()) return null
    const ch = input.peek()
    if (ch === '#') {
      skipComment()
      return readNext()
    }
    if (ch === '"') return readString()
    if (isDigit(ch)) return readNumber()
    if (isIdStart(ch)) return readIdent()
    if (isPunc(ch)) return {
      type: 'punc',
      value: input.next()
    }
    if (isOpChar(ch)) return {
      type: 'op',
      value: readWhile(isOpChar)
    }
    input.croak(`Can't handle character: ${ch}`)
  }

  const peek = () => {
    return current || (current = readNext())
  }

  const next = () => {
    let tok = current
    current = null
    return tok || readNext()
  }

  const eof = () => (peek() == null)
  
  return {
    next: next,
    peek: peek,
    eof: eof,
    croak: input.croak
  }
}

function parse(input) {
  const PRECEDENCE = {
    '=': 1,    // assign
    ':': 1,    // assign for props inside literals
    '||': 2,   // bool or
    '&&': 3,   // bool and
    '<': 4,    // les
    '>': 4,    // more
    '<=': 4,   // les or equal
    '>=': 4,   // more or equal
    '==': 4,   // equal
    '!=': 4,   // not equal
    '+': 5,    // plus
    '-': 5,    // minus
    '*': 6,    // multiple
    '/': 6,    // divide
    '%': 6,    // remaining from dividing
    '->': 7,   // access to props
    'as': 7,   // forEach var identifier
  }

  return parseTopLevel()

  function isPunc(ch) {
    const tok = input.peek()
    return (tok && (tok.type === 'punc') && (!ch || tok.value === ch))
  }

  function isKw(kw) {
    const tok = input.peek()
    return (tok && (tok.type === 'kw') && (!kw || tok.value === kw))
  }

  function isOp(op) {
    const tok = input.peek()
    console.log('op tok', tok)
    return (tok && (tok.type === 'op') && (!op || tok.value === op))
  }

  function skipPunc(ch) {
    if (isPunc(ch)) input.next()
    // else input.croak("Expecting punctuation: \"" + ch + "\"")
  }

  function skipKw(kw) {
    if (isKw(kw)) input.next()
    else input.croak("Expecting keyword: \"" + kw + "\"")
  }

  function unexpected() {
    input.croak("Unexpected token: " + JSON.stringify(input.peek()))
  }

  function maybeBinary(left, myPrec) {
    const tok = input.peek()
    if (tok) {
      const hisPrec = PRECEDENCE[tok.value]
      if (hisPrec > myPrec) {
        input.next()
        let type
        switch(tok.value) {
          case '=': {
            type = 'assignExpression'
            break
          }
          case ':': {
            type = 'literalAssignExpression'
            break
          }
          case '->': {
            type = 'memberExpression'
            break
          }
          case 'as': {
            type = 'identifierExpression'
            break
          }
          default: {
            type = 'binaryExpression'
          }
        }

        return maybeBinary({
          type,
          operator: tok.value,
          left,
          right: maybeBinary(parseAtom(), hisPrec)
        }, myPrec)
      }
    }
    return left
  }

  function delimited(start, stop, separator, parser) {
    const a = []
    let first = true
    skipPunc(start)
    while (!input.eof()) {
      if (isPunc(stop)) break
      if (first) {
        first = false
      } else {
        skipPunc(separator)
      }
      if (isPunc(stop)) break
      a.push(parser())
    }
    skipPunc(stop)
    return a
  }

  function parseCall(func) {
    return {
      type: 'call',
      func,
      args: delimited('(', ')', ',', parseExpression),
    }
  }

  function parseVarTestName() {
    skipKw('test')
    const name = input.next()
    return {
      type: 'testVar',
      name: name.value
    }
  }

  function parseVarQuestionName() {
    skipKw('question')
    const name = input.next()
    return {
      type: 'questionVar',
      name: name.value
    }
  }

  function parseIf() {
    skipKw('if')
    const cond = parseExpression()
    if (!isPunc('{')) skipKw('then')
    const then = parseExpression()
    const ret = {
      type: 'ifStatement',
      cond,
      then,
    }
    if (isKw('else')) {
      input.next()
      ret.else = parseExpression()
    }
    return ret
  }

  function parseForEach() {
    skipKw('forEach')
    const inner = parseExpression()
    const body = parseExpression()
    const ret = {
      type: 'forEachStatement',
      inner,
      body,
    }
    return ret
  }

  function parseBool() {
    return {
      type: 'bool',
      value: (input.next().value === 'true')
    }
  }

  // check does it a function call
  function maybeCall(expr) {
    return isPunc('(') ? parseCall(expr) : expr
  }

  function parseAtom() {
    const expr = (() => {
      if (isPunc('(')) {
        input.next()
        const exp = parseExpression()
        skipPunc(')')
        return exp
      }
      if (isPunc('{')) return parseProg()
      if (isPunc('[')) return parseObjLiteral()
      if (isKw('if')) return parseIf()
      if (isKw('forEach')) return parseForEach()
      if (isKw('true') || isKw('false')) return parseBool()
      if (isKw('test')) return parseVarTestName()
      if (isKw('question')) return parseVarQuestionName()

      const tok = input.next()
      if (
        (tok.type === 'var') ||
        (tok.type === 'num') ||
        (tok.type === 'str')
      ) {
        return tok
      }
      unexpected()
    })()

    return maybeCall(expr)
  }

  function parseTopLevel() {
    const prog = []
    while (!input.eof()) {
      prog.push(parseExpression())
      if (!input.eof()) {
        skipPunc(';')
      }
    }

    return {
      type: 'prog',
      prog,
    }
  }

  function parseProg() {
    const prog = delimited('{', '}', ';', parseExpression)
    if (prog.length === 0) {
      return {
        type: 'bool',
        value: false,
      }
    }
    if (prog.length === 1) {
      return prog[0]
    }

    return {
      type: 'prog',
      prog: prog
    }
  }

  function parseObjLiteral() {
    const properties = delimited('[', ']', ',', parseExpression)
    return {
      type: 'objLiteral',
      properties,
    }
  }

  function parseExpression() {
    return maybeCall(maybeBinary(parseAtom(), 0))
  }
}
