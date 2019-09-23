Program: opt_funct_decl ;

opt_funct_decl: funct_head body ;

funct_head: funct_name PAREN_OP param_list_opt PAREN_CL ;

funct_name: func_type ID ;

funct_type: STATIC_TOKEN decl_type ;

decl_type: VOID_TYPE |INT TYPE | ANYTYPE | BOOLEAN_TYPE | REAL_TYPE | DATE_TYPE
	   | STRING_TYPE ;

param_list_opt: decl_param | param_list_opt + COMA + decl_param | EPSILON ;

decl_param: decl_type ID ;

body: BRACK_OP stmt_list BRACK_CL ;

stmt_list: stmts ;

stmts: stmt | EPSILON ;

stmt: while_stmt | if_stmt | expr_stmt | return_stmt ;

if_stmt: IF PAR_OP bool_expre PAR_CL body ;

while_stmt: WHILE PAR_OP bool_expr PAR_CL body ;

return_stmt: RETURN SEMICOLON | RETURN constant SEMICOLON ;

expr_stmt: assign_stmt SEMICOLON | function_stmt ; 

assign_stmt: decl_type ID ASSIGN constant ;

function_stmt: decl_type ID PAR_OP param_list_opt PAR_CL SEMICOLON ;

bool_expr: bool_constant | constant LOG_OP constant | constant REL_OP constant ;

bool_constant: TRUE_LITERAL | FALSE_LITERAL ;

constant: INT_LITERAL | REAL_LITERAL
	  | DATE_LITERAL | STRING_LITERAL ;



INT_TYPE: 'int';
ANYTYPE_TYPE: 'anytype';
BOOLEAN_TYPE: 'boolean';
VOID_TYPE: 'void';
REAL_TYPE: 'real' ;
STRING_TYPE: 'String';
DATE_TYPE: 'date' ;

SEMICOLON: ';' ;
PAR_OP: '(' ;
PAR_CL: ')' ;
BRACK_OP: '{' ;
BRACK_CL: '}' ;
COMA: ',' ;
EPSILON: E

FALSE_LITERAL: 'false';
TRUE_LITERAL: 'true';
INT_LITERAL: (DIGIT)+ ;
REAL_LITERAL: (DIGIT)+ '.' (DIGIT)+ ;
STRING_LITERAL: '"' (LETTER | DIGIT | ' ' | '%' | '@' | ',' | '-' | '=' | '(' | ')' | '_')* '"';
DATE_LITERAL: DIGIT DIGIT '/' DIGIT DIGIT '/' DIGIT DIGIT DIGIT DIGIT ;

DIGIT : [0-9] ;
LETTER : [a-zA-Z] ;
