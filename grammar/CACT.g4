grammar CACT;

@header {
    #include "cact_types.h"
    #include "SymbolTable.h"
    #include <vector>
    #include <string>
}

/****** parser ******/

/*** 声明&定义 ***/
compUnit
    : (decl | funcDef)+ EOF;

decl
    : constDecl
    | varDecl
    ;

constDecl
    : CONST bType constDef (COMMA constDef)* SEMICOLON
    ;

bType
    locals[
        cact_basety_t basety,
        std::vector<cact_basety_t*> passTo, 
    ]
    : INT
    | BOOL
    | FLOAT
    | DOUBLE
    ;

//为了方便在enterconst/varDef时为constinitval获取维度数组，提取该部分
arrayDims
    locals[
        std::vector<uint32_t> *dims_ptr,
    ]
    : (LeftBracket IntConst RightBracket)*
    ;

constDef
    locals [
        //由同级btype填充
        cact_basety_t basety,
        std::vector<uint32_t> arraydims,
        std::string name,
        cact_type_t type,
    ]
    : Ident arrayDims ASSIGN constInitVal
    ;

constInitVal
    locals[
        //自顶向下继承
        cact_basety_t basety,
        //维度数组指针，值依次是从最外层到最内层的维度
        std::vector<uint32_t> *dims_ptr,
        //维度索引，最内层为0
        uint16_t dim_index,
        //表征是否最顶层，只有index为1，且为最顶层才允许以平铺列表初始化
        bool top,
        
        //IR
        //value_list为所有子元素拼接，空位置用#占位
        std::string value_list,
    ]
    : constExp 
    | LeftBrace (constInitVal (COMMA constInitVal)*)? RightBrace
    ;

varDecl
    : bType varDef (COMMA varDef)* SEMICOLON
    ;

varDef
    locals[
        //由同级btype填充
        cact_basety_t basety,
        std::vector<uint32_t> arraydims,
        std::string name,
        cact_type_t type,
    ]
    : Ident arrayDims (ASSIGN constInitVal)?
    ;

//省去中间的funcFParams，直接在funcDef中生成形参列表，避免形参列表的过多传递
//在funcDef中定义列表，并将其指针传递给funcFParam填充
funcDef
    locals[
        //由funcDef管理，funcFParam负责插入
        //用于函数声明以及添加到block作用域
        fparam_list_t fparam_list,
    ]
    : funcType Ident LeftParen funcFParam? (COMMA funcFParam)* RightParen block
    ;

funcType
    locals[
        cact_basety_t basety,
    ]
    : VOID
    | INT
    | FLOAT
    | DOUBLE
    | BOOL
    ;

funcFParam
    locals[
        //指向fparam_list的指针，用于查找重复命名和插入
        fparam_list_t *fparam_list_ptr,
        //由父节点确定的次序
        int order,
    ]
    : bType Ident (LeftBracket (IntConst)? RightBracket (LeftBracket IntConst RightBracket)*)?
    ;

/*** 语句&表达式 ***/
//考虑到直接从block获取最后一个decl|stmt，省略blockItem
//由于只检查特定位置的stmt返回类型，使用自底向上的综合属性
//空节点，用于label的跳入和跳出
lab
    locals[
        std::string in_label,
    ]
    :
    ;

go
    locals[
        std::string out_label,
    ]
    :
    ;

block
    locals[
        cact_basety_t ret_type,
        //形参列表添加到block作用域
        fparam_list_t *fparam_list_ptr,
        //考虑到break和continue可能存在block内，作为中间过程传递
        std::string break_label,
        std::string continue_label,
    ]
    : LeftBrace (decl|stmt)* RightBrace
    ;

stmt
    locals[
        cact_basety_t ret_type,
        //IR
        //长度非空时，enter时跳进到in_label，exit跳出到out_label
        std::string in_label,
        std::string out_label,
        //因为不知道break和continue层级，在每个stmt/block->stmt/block推导时传递
        std::string break_label,
        std::string continue_label,
    ]
    : lVal ASSIGN exp SEMICOLON                                         #stmt_assign
    | (exp)? SEMICOLON                                                  #stmt_exp
    | block                                                             #stmt_block
    | IF LeftParen cond RightParen lab stmt (go lab ELSE stmt)? lab     #stmt_if
    | lab WHILE LeftParen cond RightParen lab stmt go lab               #stmt_while
    | (BREAK | CONTINUE | RETURN exp?) SEMICOLON                        #stmt_bcr
    ;

exp 
    locals[
        cact_expr_ptr self,
        //IR
        std::string result_name,
    ]
    : BoolConst
    | addExp 
    ;

constExp
    locals[
        cact_basety_t basety,
        //IR
        std::string valstr,
    ]
    : number
    | BoolConst
    ;

cond
    locals[
        //IR
        std::string true_label,
        std::string false_label,
    ]
    : lOrExp
    ;

//对于有中括号的，为子数组/元素，需要进行维度检查
//不允许对子数组赋值（不允许类型转换）
//为方便赋值操作对象检查，将lVal也当做表达式进行管理，子数组op为OP_ARRAY，元素op为OP_BASE
lVal
    locals[
        cact_expr_ptr self,
        //仅用于赋值时检查是否常量
        bool is_const,
        
        //IR
        // //区分应用场景：赋值ST 1，使用LD 0 
        // bool is_store,
        //使用">n"表示偏移n个元素
        std::string result_name,
    ]
    : Ident (LeftBracket exp RightBracket)*
    ;

primaryExp
    locals[
        cact_expr_ptr self,
        //IR
        //结果变量名，下同
        std::string result_name,
    ]
    : number
    | lVal
    | LeftParen exp RightParen
    ;

//为方便管理，将number也设置为表达式
//op为OP_BASE，表示终结符常量
number
    locals[
        cact_expr_ptr self,
    ]
    : addOp ? ( IntConst | DoubleConst | FloatConst )
    ;

unaryExp
    locals[
        cact_expr_ptr self,
        //IR
        std::string result_name,
    ]
    : primaryExp
    | unaryOp unaryExp
    | Ident LeftParen (funcRParams)? RightParen
    ;

//将操作符的可能集合独立处理，方便在对应Exp中直接使用getText获取
unaryOp
    : addOp | NOT 
    ;
funcRParams
    : exp (COMMA exp)*
    ;

mulExp
    locals[
        cact_expr_ptr self,
        //IR
        std::string result_name,
    ]
    : unaryExp
    | mulExp mulOp unaryExp
    ;

mulOp
    : MUL | DIV | MOD
    ;

addExp
    locals[
        cact_expr_ptr self,
        //IR
        std::string result_name,
    ]
    : mulExp
    | addExp addOp mulExp
    ;

addOp
    : POS_ADD | NEG_SUB
    ;

//代码设计中只支持简单的条件运算，不支持复杂组合，例如a==b==c，a<b != c>d等
//因此可省略relExp和eqExp作为中间运算的情形

relExp  
    locals[
        cact_expr_ptr self,
        //IR
        std::string result_name,
        std::string true_label,
        std::string false_label,
        //该节点能否使用label
        bool has_label,
    ]
    : addExp
    | relExp relOp addExp
    | BoolConst
    ;

relOp
    : LEQ | GEQ | LT | GT
    ;

eqExp
    locals[
        cact_expr_ptr self,
        //IR
        std::string result_name,
        std::string true_label,
        std::string false_label,
        bool has_label,
    ]
    : relExp
    | eqExp eqOp relExp
    ;

eqOp
    : EQ | NEQ
    ;

lAndExp
    locals[
        cact_expr_ptr self,
        //IR
        std::string true_label,
        std::string false_label,
        std::string in_label,
    ]
    : eqExp
    | lAndExp AND lab eqExp
    ;

lOrExp
    locals[
        cact_expr_ptr self,
        //IR
        std::string true_label,
        std::string false_label,
    ]
    : lAndExp
    | lOrExp OR lab lAndExp
    ;

/****** lexer  ******/
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
fragment TRUE        : 'true'    ;
fragment FALSE       : 'false'   ;

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
POS_ADD     : '+'       ;
NEG_SUB     : '-'       ;
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

/* 终结符 */
BoolConst
    : TRUE
    | FALSE
    ;

Ident
    : [a-zA-Z_] [a-zA-Z_0-9]*
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
    : ('0x'|'0X') [0-9a-fA-F]+
    ;


FloatConst
    : PreFloatDouble ('f' | 'F')
    ;

DoubleConst 
    : PreFloatDouble
    ;

fragment PreFloatDouble
    : Fraction Exponent?
    | [0-9]+ Exponent
    ;
fragment Fraction
    : [0-9]+ '.' [0-9]+
    | [0-9]+ '.'
    | '.' [0-9]+
    ;

fragment Exponent
    : ('E' | 'e') (POS_ADD|NEG_SUB)? [0-9]+
    ;


/****** skips  ******/
NewLine
    :(
        '\r' '\n'?
        | '\n'
    )
    -> skip
    ;

WhiteSpace
    :(
        [ \t]+
    ) 
    -> skip
    ;

//检查是否\r\n要放在一起
LineComment
    :(
        '//' ~[\r\n]*
    )
    -> skip
    ;

BlockComment
    :(
        '/*' .*? '*/'
    )
    ->skip
    ;
