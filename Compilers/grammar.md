```
PrimaryExpression	::=	"this"
                  |	ObjectLiteral
                  | Identifier
Identifier	::=	<IDENTIFIER_NAME>
ObjectLiteral	::=	"[" ( PropertyNameAndValueList )? "]"
PropertyNameAndValueList	::=	PropertyNameAndValue ( ","PropertyNameAndValue | "," )*
PropertyNameAndValue	::=	PropertyName ":" AssignmentExpression
PropertyName ::=	Identifier
             |	<STRING_LITERAL>
RelationalOperator	::=	( "<" | ">" | "<=" | ">=" )
MemberExpression	::=	MemberExpressionPart
MemberExpressionPart	::=	( "->" Identifier )
AssignmentOperator	::=	( "=" )
Expression	::=	AssignmentExpression ( "," AssignmentExpression )*
Statement	::=	Block
          |	IfStatement
          |	IterationStatement
Block	::=	"{" ( StatementList )? "}"
StatementList	::=	( Statement )
VariableStatement	::=	"test" VariableDeclarationList
                  | "question" VariableDeclarationList
VariableDeclarationList	::=	VariableDeclaration ( "," VariableDeclaration )*
VariableDeclaration	::=	Identifier ( Initialiser )?
IfStatement	::=	"if" "(" Expression ")" Statement ( "else" Statement )?
IterationStatement	::=	( "forEach" VariableStatement "as" VariableDeclaration)
```
