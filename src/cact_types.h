#pragma once

#include <vector>
#include <map>
#include <memory>

typedef enum {
    BTY_UNKNOWN = 0,
    BTY_VOID,
    BTY_INT,
    BTY_BOOL,
    BTY_FLOAT,
    BTY_DOUBLE,
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
    OP_ADD,
    OP_SUB,
    OP_NOT,
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
    //作为维度长度，只有当op为OP_BASE且basety为int时才会使用
    int             int_result;
    //作为函数实参，只有当op为OP_ARRAY时使用
    arrdims_t       arrdims;
}cact_expr_t;

//使用map用于实现类型的标号、字符串及大小的转换
class TypeUtils {
    public:
    std::map <std::string, cact_basety_t> str_to_val{
        {"void",    BTY_VOID},
        {"int",     BTY_INT},
        {"bool",    BTY_BOOL},
        {"float",   BTY_FLOAT},
        {"double",  BTY_DOUBLE},
    };
    std::map <cact_basety_t, std::string> val_to_str{
        {BTY_VOID,  "void"},
        {BTY_INT,   "int"},
        {BTY_BOOL,  "bool"},
        {BTY_FLOAT, "float"},
        {BTY_DOUBLE,"double"},
    };
    std::map <cact_basety_t, size_t> val_to_size{
        {BTY_VOID,  8},
        {BTY_INT,   4},
        {BTY_BOOL,  1},
        {BTY_FLOAT, 4},
        {BTY_DOUBLE,8},
    };
    std::map <std::string, cact_op_t> str_to_op{
        {"=",   OP_ASSIGN},
        {"+",   OP_ADD},
        {"-",   OP_SUB},
        {"!",   OP_NOT},
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
};

//定义在main中
extern TypeUtils typeutils;
