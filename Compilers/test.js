var ast2 = parse(TokenStream(InputStream(`
  var a = [
    b: 45,
    c: 71,
  ];
  #var a = {
  #  foo: 'bar',
  #};
  # var b = 5;
  # if(a <= b) {
  #  return true;
  # }
`)));






const ts = TokenStream(InputStream('1 + 2'))
console.log('ts', ts)

// var ast1 = parse(TokenStream(InputStream('1 + 2')));
var ast2 = parse(TokenStream(InputStream(`
  var a = [
    b: 45,
    c: 71,
  ];
  #var a = {
  #  foo: 'bar',
  #};
  # var b = 5;
  # if(a <= b) {
  #  return true;
  # }
`)));

// console.log('ast1', JSON.stringify(ast1, null, 2))
console.log('ast2', JSON.stringify(ast2, null, 2))

// var ast1 = parse(TokenStream(InputStream('1 + 2')))

// const ast1 = parse(TokenStream(InputStream('f(1, 3 + 4, 5)')))
// const ast1 = parse(TokenStream(InputStream('(1 + 3)')))
// console.log('ast1', JSON.stringify(ast1, null, 2))
