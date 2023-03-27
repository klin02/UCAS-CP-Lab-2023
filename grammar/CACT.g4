grammar CACT;

@header {
    #include <vector>
}

/****** parser ******/

/*** 声明&定义 ***/
compUnit
    : (decl | funcDef)+ EOF ;

decl
    : constDecl
    | varDecl
    ;

constDecl
    : CONST bType constDef (COMMA constDef)* SEMICOLON
    ;

bType
    : INT
    | BOOL
    | FLOAT
    | DOUBLE
    ;

constDef
    : Ident (LeftBracket IntConst RightBracket)* '=' constInitVal
    ;

constInitVal
    : constExp 
    | LeftBrace (constInitVal (COMMA constInitVal)*)? RightBrace
    ;

varDecl
    : bType varDef (COMMA varDef)* SEMICOLON
    ;

varDef
    : Ident (LeftBracket IntConst RightBracket)* ('=' constInitVal)?
    ;

funcDef
    : funcType Ident LeftParen (funcFParams)? RightParen block
    ;

funcType
    : VOID
    | INT
    | FLOAT
    | DOUBLE
    | BOOL
    ;

funcFParams
    : funcFParam (COMMA funcFParam)*
    ;

funcFParam
    : bType Ident (LeftBracket (IntConst)? RightBracket (LeftBracket IntConst RightBracket)*)?
    ;

/*** 语句&表达式 ***/
block
    : LeftBrace (blockItem)* RightBrace
    ;

blockItem
    : decl
    | stmt
    ;

stmt
    : block
    | lVal ASSIGN exp SEMICOLON
    | (exp)? SEMICOLON
    | IF LeftParen cond RightParen stmt (ELSE stmt)?
    | WHILE LeftParen cond RightParen stmt
    | (BREAK | CONTINUE | RETURN exp) SEMICOLON
    ;

exp 
    : addExp 
    | BoolConst
    ;

constExp
    : number
    | BoolConst
    ;

cond
    : lOrExp
    ;

lVal
    : Ident (LeftBracket exp RightBracket)*
    ;

primaryExp
    : number
    | lVal
    | LeftParen exp RightParen
    ;

number
    : IntConst
    | DoubleConst
    | FloatConst
    ;

unaryExp
    : primaryExp
    | (ADD | SUB | NOT) unaryExp
    | Ident LeftParen (funcRParams)? RightParen
    ;

funcRParams
    : exp (COMMA exp)*
    ;

mulExp
    : unaryExp
    | mulExp (MUL | DIV | MOD) unaryExp
    ;

addExp
    : mulExp
    | addExp (ADD | SUB) mulExp
    ;

//考虑是否需要BoolConst
relExp
    : addExp
    | relExp (LEQ | GEQ | LT | GT) addExp
    ;

eqExp
    : relExp
    | eqExp (EQ | NEQ) relExp
    ;

lAndExp
    : eqExp
    | lAndExp (AND) eqExp
    ;

lOrExp
    : lAndExp
    | lOrExp (OR) lAndExp
    ;

/****** lexer  ******/
/* 终结符 */
Ident
    : [a-zA-Z_] [a-zA-Z_0-9]*
    ;

BoolConst
    : TRUE
    | FALSE
    ;

IntConst 
    : DecimalConst 
    | OctalConst 
    | HexadecConst
    ;

fragment DecimalConst
    : '0'
    | [1-9] [0-9]*
    ;

fragment OctalConst
    : '0' [0-7]+
    ;

fragment HexadecConst
    : ('0x' | '0X') [0-9a-fA-F]+
    ;

FloatConst
    : DoubleConst ('f' | 'F')
    ;

DoubleConst 
    : Fraction Exponent?
    | [0-9]+ Exponent
    ;

fragment Fraction
    : [0-9]+ '.' [0-9]+
    | [0-9]+ '.'
    | '.' [0-9]+
    ;

fragment Exponent
    : ('E' | 'e') (ADD | SUB)? [0-9]+
    ;

/* 标点 */
LeftParen   : '('       ;
RightParen  : ')'       ;
LeftBracket : '['       ;
RightBracket: ']'       ;
LeftBrace   : '{'       ;
RightBrace  : '}'       ;
SEMICOLON   : ';'       ;
COMMA       : ','       ;

/* 关键字 */
TRUE        : 'true'    ;
FALSE       : 'false'   ;

CONST       : 'const'   ;
VOID        : 'void'    ;
INT         : 'int'     ;
BOOL        : 'bool'    ;
FLOAT       : 'float'   ;
DOUBLE      : 'double'  ;

IF          : 'if'      ;
ELSE        : 'else'    ;
WHILE       : 'while'   ;
BREAK       : 'break'   ;
CONTINUE    : 'continue';
RETURN      : 'return'  ;

/* 运算符号 */
ASSIGN      : '='       ;
ADD         : '+'       ;
SUB         : '-'       ;
NOT         : '!'       ;
MUL         : '*'       ;
DIV         : '/'       ;
MOD         : '%'       ;
LEQ         : '<='      ;
GEQ         : '>='      ;
LT          : '<'       ;
GT          : '>'       ;
EQ          : '=='      ;
NEQ         : '!='      ;
AND         : '&&'      ;
OR          : '||'      ;

/****** skips  ******/
NewLine
    :(
        '\r' ('\n')?
        | '\n'
    )
    -> skip
    ;

WhiteSpace
    :(
        ' '
        | '\t'
    )
    -> skip
    ;

//检查是否\r\n要放在一起
LineComment
    :(
        '//' (~('\r' | '\n'))*
    )
    -> skip
    ;

BlockComment
    :(
        '/*' .*? '*/'
    )
    ->skip
    ;
