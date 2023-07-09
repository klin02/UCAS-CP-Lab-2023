#pragma once

#include <iostream>
#include "cact_types.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"
#include "IROptim.h"

extern SemanticAnalysis semantic_analysis;
extern IROptim          ir_optim;

#ifdef ASM_gen
class RiscvGen{
    public:
        size_t imm_cnt = 0; //浮点立即数计数
        //缓存全局变量、局部数组初始值和浮点立即数
        std::vector<std::string> Const_Stack;
        std::vector<std::string> ASM_array;
        size_t frame_size;  //计算栈帧
        size_t iparam_order=0;    //记录当前传递第几个整形参数
        size_t fparam_order=0;
        //从名字去除前缀，并转为数字
        int num_from_name(std::string name){
            return std::stoi(name.substr(1));
        }

        //将base向上对齐到align倍数
        int up_to_align(int base,int align){
            int div = base / align;
            int mod = base % align;
            base = (mod==0)? base : (div+1)*align;
        }

        //传入basety,初始值长度和字符串，将其解析并写入Const_Stack
        void stack_initval(std::string initval_str, cact_basety_t basety, int len);

        //通用API，传入名字和reg，解析名字，将对应的内容存到reg上，并写入ASM_array
        void var_to_reg(std::string var_name,std::string reg_name);
        //将值从寄存器写到栈上
        void reg_to_var(std::string var_name,std::string reg_name);

        void Gen_All(std::string outfile);
        
        void Gen_Label(IR_code_t &irc);
        void Gen_FuncBegin(IR_code_t &irc);
        void Gen_FuncEnd(IR_code_t &irc);
        void Gen_Param(IR_code_t &irc);
        void Gen_Call(IR_code_t &irc);
        void Gen_Return(IR_code_t &irc);
        void Gen_Assign(IR_code_t &irc);
        void Gen_Operation(IR_code_t &irc);
        void Gen_Branch(IR_code_t &irc);
        void Gen_Jump(IR_code_t &irc);
        void Gen_G_Alloc(IR_code_t &irc);
        void Gen_L_Alloc(IR_code_t &irc);
        
        void Cnt_FuncParam(std::string func_name);
        void Cnt_Temp_Lvar(std::string var_name);
};
#endif