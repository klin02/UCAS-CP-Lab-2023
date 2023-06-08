#pragma once

#ifdef ASM_gen
#include "cact_types.h"
#include "SymbolTable.h"

extern SemanticAnalysis semantic_analysis;

class RiscvGen{
    public:
        std::vector<std::string> ASM_array;

        void Gen_All(std::string outfile);
        
        void Gen_Label(IR_code_t &irc);
        void Gen_FuncBegin(IR_code_t &irc);
        void Gen_FuncEnd(IR_code_t &irc);
        void Gen_Param(IR_code_t &irc);
        void Gen_Call(IR_code_t &irc);
        void Gen_Return(IR_code_t &irc);
        void Gen_Load(IR_code_t &irc);
        void Gen_Store(IR_code_t &irc);
        void Gen_BinaryOp(IR_code_t &irc);
        void Gen_UnaryOp(IR_code_t &irc);
        void Gen_Branch(IR_code_t &irc);
        void Gen_Jump(IR_code_t &irc);
        void Gen_Alloc(IR_code_t &irc);
        
};
#endif