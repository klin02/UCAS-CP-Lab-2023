#pragma once

#include <vector>
#include <map>
#include <memory>

#define IR_gen  //宏定义 开启中间代码生成
#define ASM_gen

typedef enum {
    BTY_UNKNOWN = 0,
    BTY_VOID,
    BTY_INT,
    BTY_BOOL,
    BTY_FLOAT,
    BTY_DOUBLE,
    BTY_INT_PTR,
    BTY_BOOL_PTR,
    BTY_FLOAT_PTR,
    BTY_DOUBLE_PTR,
} cact_basety_t;

typedef std::vector<uint32_t> arrdims_t;
typedef struct {
    bool            is_const;
    cact_basety_t   basety;
    //针对非数组，vector的size为0
    //针对多维数组，逐一列出维度
    arrdims_t       arrdims; 
} cact_type_t;

//OP_BASE  标志 基本常量 (直接由终结符推出)
//OP_ARRAY 标志 左值子数组
//OP_ITEM  标志 左值(const)变量，数组元素
typedef enum{
    OP_UNKNOWN = 0,
    OP_BASE,
    OP_ARRAY,
    OP_ITEM,
    OP_ASSIGN,
    OP_POS,
    OP_NEG,
    OP_NOT,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_LEQ,
    OP_GEQ,
    OP_LT,
    OP_GT,
    OP_EQ,
    OP_NEQ,
    OP_AND,
    OP_OR,
} cact_op_t;


//占位声明
struct cact_expr;
//sharedptr可以指向同一个结构体，避免结构体的连续赋值。该结构体生存周期是sharedptr指针的并集
//注意：不能将临时变量的地址赋给共享指针，而应当在共享指针创建内创建对象
typedef std::shared_ptr<cact_expr> cact_expr_ptr;
//指向子表达式的指针数组
typedef std::vector<cact_expr_ptr> subexprs_t;
typedef struct cact_expr{
    cact_op_t       op;
    cact_basety_t   basety;
    subexprs_t      subexprs;
    //作为函数实参，只有当op为OP_ARRAY时使用
    arrdims_t       arrdims;
}cact_expr_t;

#ifdef IR_gen
typedef enum{
    IR_UNKNOWN=0,
    IR_LABEL,
    IR_FUNC_BEGIN,
    IR_FUNC_END,
    IR_PARAM,
    IR_CALL,
    IR_RETURN,
    IR_ASSIGN,
    IR_ADD,
    IR_SUB,
    IR_MUL,
    IR_DIV,
    IR_MOD,
    IR_AND,
    IR_OR,  
    IR_NEG,
    IR_NOT,
    IR_BEQ,
    IR_BNE,
    IR_BLT,
    IR_BGT,
    IR_BLE,
    IR_BGE,
    IR_J,
    IR_G_ALLOC,    //全局变量声明
    IR_L_ALLOC,    //局部变量声明
}IR_op_t;

typedef struct{
    IR_op_t IRop;
    cact_basety_t basety;
    std::string result;
    std::string arg1;
    std::string arg2;
}IR_code_t;

typedef struct{
    cact_basety_t basety;
    bool is_const;
    size_t length;
    size_t offset;
}IR_temp_t;
#endif

//使用map用于实现类型的标号、字符串及大小的转换
class TypeUtils {
    public:
    std::map <std::string, cact_basety_t> str_to_basety{
        {"void",    BTY_VOID},
        {"int",     BTY_INT},
        {"bool",    BTY_BOOL},
        {"float",   BTY_FLOAT},
        {"double",  BTY_DOUBLE},
    };
    std::map <cact_basety_t, std::string> basety_to_str{
        {BTY_VOID,      "void"},
        {BTY_INT,       "int"},
        {BTY_BOOL,      "bool"},
        {BTY_FLOAT,     "float"},
        {BTY_DOUBLE,    "double"},
        {BTY_UNKNOWN,   "unknown"},
        {BTY_INT_PTR,   "int_ptr"},
        {BTY_BOOL_PTR,  "bool_ptr"},
        {BTY_FLOAT_PTR, "float_ptr"},
        {BTY_DOUBLE_PTR,"double_ptr"},
    };
    std::map <cact_basety_t, size_t> basety_to_size{
        {BTY_VOID,  0},
        {BTY_INT,   4},
        {BTY_BOOL,  1},
        {BTY_FLOAT, 4},
        {BTY_DOUBLE,8},
        {BTY_INT_PTR,   8},
        {BTY_BOOL_PTR,  8},
        {BTY_FLOAT_PTR, 8},
        {BTY_DOUBLE_PTR,8},
    };
    std::map <std::string, cact_op_t> str_to_op{
        {"=",   OP_ASSIGN},
        //unaryOp通过后缀U进行区分，统一后缀方便API
        {"+U",  OP_POS},
        {"+",   OP_ADD},
        {"-U",  OP_NEG},
        {"-",   OP_SUB},
        {"!U",  OP_NOT},
        {"*",   OP_MUL},
        {"/",   OP_DIV},
        {"%",   OP_MOD},
        {"<=",  OP_LEQ},
        {">=",  OP_GEQ},
        {"<",   OP_LT},
        {">",   OP_GT},
        {"==",  OP_EQ},
        {"!=",  OP_NEQ},
        {"&&",  OP_AND},
        {"||",  OP_OR},
    };

    #ifdef IR_gen
    std::map <cact_op_t, IR_op_t> op_to_IRop{
        {OP_NEG, IR_NEG},
        {OP_NOT, IR_NOT},
        {OP_ADD, IR_ADD},
        {OP_SUB, IR_SUB},
        {OP_MUL, IR_MUL},
        {OP_DIV, IR_DIV},
        {OP_MOD, IR_MOD},
        {OP_LEQ, IR_BLE},
        {OP_GEQ, IR_BGE},
        {OP_LT,  IR_BLT},
        {OP_GT,  IR_BGT},
        {OP_EQ,  IR_BEQ},
        {OP_NEQ, IR_BNE},
    };

    std::map <IR_op_t, std::string> IRop_to_str{
        {IR_LABEL,      "Label"},
        {IR_FUNC_BEGIN, "Func Begin"},
        {IR_FUNC_END,   "Func End"},
        {IR_PARAM,      "Param"},
        {IR_CALL,       "Call"},
        {IR_RETURN,     "Return"},
        {IR_ASSIGN,     "ASSIGN"},
        {IR_ADD,        "ADD"},
        {IR_SUB,        "SUB"},
        {IR_MUL,        "MUL"},
        {IR_DIV,        "DIV"},
        {IR_MOD,        "MOD"},
        {IR_AND,        "AND"},
        {IR_OR,         "OR"},
        {IR_NEG,        "NEG"},
        {IR_NOT,        "NOT"},
        {IR_BEQ,        "BEQ"},
        {IR_BNE,        "BNE"},
        {IR_BLT,        "BLT"},
        {IR_BGT,        "BGT"},
        {IR_BLE,        "BLE"},
        {IR_BGE,        "BGE"},
        {IR_J,          "J"},
        {IR_G_ALLOC,    "G_Alloc"},//全局变量声明
        {IR_L_ALLOC,    "L_Alloc"},//局部变量声明
    };
    #endif
};

//定义在main中
extern TypeUtils typeutils;
