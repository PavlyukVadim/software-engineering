## Theory of compilers

### Implementation of specific programming language for testing system

### Getting started

```
test t = [
  title: "My first test",
]

question q1 = [
  description: "What's your name",
]

question q2 = [
  description: "How old are you",
]

question q3 = []

t->questions->add(q1)
t->questions->add(q2)
t->questions->add(q3)
t->questions->remove(q3)

# t->questions->amount 2

if (t->questions->amount > 1) {
  print("questions amount more than 1")
}

t->answers->add([
  id: 1,
  q1: "Vadim",
  q2: "21",
])

t->answers->add([
  id: 2,
  q1: "Max",
  q2: "25",
])

forEach(t->questions->items as q) {
  print(q->description)
}

forEach(t->answers->items as a) {
  print(q1->description, a->q1)
}
```

### Implementation

Input Stream -> Token Stream -> Parsing into AST -> Evaluation

### BNF

```
PrimaryExpression	::=
  "this" |
  ObjectLiteral |
  Identifier
Identifier ::=
  <IDENTIFIER_NAME>
CommentSymbol ::=
  ("#")
ObjectLiteral	::=
  "[" (PropertyNameAndValueList)? "]"
PropertyNameAndValueList ::=
  PropertyNameAndValue (","PropertyNameAndValue | ",")*
PropertyNameAndValue ::=
  PropertyName ":" AssignmentExpression
PropertyName ::=
  Identifier |
  <STRING_LITERAL>
RelationalOperator ::=
  "<" |
  ">" |
  "<=" |
  ">="
MemberExpression ::=
  MemberExpressionPart
MemberExpressionPart ::=
  ("->" Identifier)
AssignmentOperator ::=
  ("=")
Expression ::=
  AssignmentExpression ("," AssignmentExpression)*
Statement ::=
  Block |
  IfStatement |
  IterationStatement
Block ::=
  "{" (StatementList)? "}"
StatementList	::=
  (Statement)
VariableStatement	::=
  "test" VariableDeclarationList |
  "question" VariableDeclarationList
VariableDeclarationList	::=
  VariableDeclaration ( "," VariableDeclaration )*
VariableDeclaration	::=
  Identifier (Initialiser)?
IfStatement	::=
  "if" "(" Expression ")" Statement ("else" Statement)?
IterationStatement ::=
  ("forEach" VariableStatement "as" VariableDeclaration)
```
