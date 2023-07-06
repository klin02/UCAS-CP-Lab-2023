#pragma once

#include "cact_types.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"

extern SemanticAnalysis semantic_analysis;

#ifdef IR_gen
class BasicBlock{
    public:
        //基本块使用链表连接
        class BasicBlock *pre;
        class BasicBlock *next; 

}
class IROptim{
    public:

}
#endif