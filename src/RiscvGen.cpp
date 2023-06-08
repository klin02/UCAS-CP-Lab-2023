#pragma once 

#ifdef ASM_gen

#include "RiscvGen.h"

void RiscvGen:: Gen_All(std::string asm_name){
    //添加开头信息
    ASM_array.push_back(".file   \"" + asm_name + ".cact\"");
    ASM_array.push_back(".option nopic");
    ASM_array.push_back(".attribute arch, \"rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0\"");
    ASM_array.push_back(".attribute unaligned_access, 0");
    ASM_array.push_back(".attribute stack_align, 16");

    //结尾将全部信息输入到文件
    std::ofstream outfile;
    outfile.open(asm_name);
    for(auto ASM: ASM_array){
        //除了标号和文件名，其他(无冒号)后移一个缩进
        if(ASM.find(':')==-1){
            outfile << '\t';
        }
        outfile << ASM <<std::endl;
    }
    outfile.close();
}

void RiscvGen:: Gen_Label(IR_code_t &irc){}
void RiscvGen:: Gen_FuncBegin(IR_code_t &irc){
    auto func_name = irc.result_name;
    ASM_array.push_back("");
    ASM_array.push_back(".text");
    ASM_array.push_back(".text");
    ASM_array.push_back(".align   1");
    ASM_array.push_back(".globl   " + func_name);
    ASM_array.push_back(".type    " + func_name + ", @function");
    ASM_array.push_back(func_name + ":");

}
void RiscvGen:: Gen_FuncEnd(IR_code_t &irc){}
void RiscvGen:: Gen_Param(IR_code_t &irc){}
void RiscvGen:: Gen_Call(IR_code_t &irc){}
void RiscvGen:: Gen_Return(IR_code_t &irc){}
void RiscvGen:: Gen_Load(IR_code_t &irc){}
void RiscvGen:: Gen_Store(IR_code_t &irc){}
void RiscvGen:: Gen_BinaryOp(IR_code_t &irc){}
void RiscvGen:: Gen_UnaryOp(IR_code_t &irc){}
void RiscvGen:: Gen_Branch(IR_code_t &irc){}
void RiscvGen:: Gen_Jump(IR_code_t &irc){}
void RiscvGen:: Gen_Alloc(IR_code_t &irc){}

#endif