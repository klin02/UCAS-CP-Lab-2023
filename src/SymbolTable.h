#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

#include "cact_types.h"

//定义作用域节点，以多叉树进行组织
typedef struct scope{
    struct scope *parent;
}scope_t;

//在变量表中，使用名字+作用域作为一项的key
//相比只用名字，在多层作用域都出现同名变量时能提升性能
typedef struct name_scope{
    std::string name;
    scope_t *scope_ptr;

    //由于该变量非基本类型，需要重载运算符以进行比较
    //hash表插入时会自动判断是否与已添加的重合，默认方式是指针比较，与期望不符
    bool operator==(const name_scope &other) const{
        return (other.scope_ptr == scope_ptr) && (other.name == name);
    }
} name_scope_t;

//变量表表项
typedef struct var_symbol_item{
    //整合类型，包含常量和数组信息
    cact_type_t type;
    #ifdef IR_gen
    std::string IR_name;
    #endif
} var_symbol_item_t;

//由于变量表无序性，使用基于hash的unorder_map以提高性能
//对于非基本值，需要重写hash方法
struct hash_utils{
    size_t operator()(const name_scope_t &tmp) const {
        return (std::hash<std::string>()(tmp.name) ^ std::hash<scope_t *>()(tmp.scope_ptr));
    }
};

//形参列表的一项
typedef struct fparam_item{
    std::string name;
    cact_type_t type;
    #ifdef IR_gen
    std::string IR_name;
    #endif
} fparam_item_t;

typedef std::vector<fparam_item_t>
        fparam_list_t;

//函数表表项
typedef struct func_symbol_item{
    //函数返回值只能是基本类型
    cact_basety_t ret_type;
    //对应形参列表，为对应检查，实现为有序表
    fparam_list_t fparam_list;
}func_symbol_item_t;

typedef std::unordered_map <name_scope_t, var_symbol_item_t, hash_utils> 
        var_table_t;
typedef std::unordered_map <std::string, func_symbol_item_t> 
        func_table_t;

class SymbolTable{
    public:
        scope_t *root_scope;

        //unordermap需要传入key，value和hash_func(可选)
        var_table_t var_table;
        func_table_t func_table;

        //find只能查找特定作用域的var，用于声明检查
        //deepfind将向上搜索，用于变量使用
        var_table_t::iterator deepfind(std::string name, scope_t *scope_ptr){
            auto end_flag = var_table.end();
            while (scope_ptr != NULL){
                //返回指向找到元素的迭代器
                auto iter = var_table.find((name_scope){.name=name, .scope_ptr=scope_ptr});
                if (iter != end_flag){
                    //找到该变量
                    return iter;
                }
                else 
                    scope_ptr = scope_ptr->parent;
            }
            //如果最终未找到，返回end_flag用于判断
            return end_flag;
        }   
};

//统一将全局变量定义在main，其他文件使用extern
extern SymbolTable symbol_table;

