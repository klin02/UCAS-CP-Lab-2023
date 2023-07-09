#include <iostream>
#include <string.h>

#include "antlr4-runtime.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTListener.h"

#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"
#include "IROptim.h"
#include "RiscvGen.h"

using namespace antlr4;

int                 OPTIM_LEVEL;

SyntaxAnalysis      syntax_analysis;
SymbolTable         symbol_table;
TypeUtils           typeutils;
SemanticAnalysis    semantic_analysis;
IROptim             ir_optim;
RiscvGen            riscv_gen;

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    std::string cact_path;
    if(argc==2){
        OPTIM_LEVEL = 0;
        stream.open(argv[1]);
        cact_path = argv[1];
    }
    else{
        if(strcmp(argv[1],"-O0")==0)
            OPTIM_LEVEL = 0;
        else if(strcmp(argv[1],"-O1")==0)
            OPTIM_LEVEL = 1;
        else if(strcmp(argv[1],"-O2")==0)
            OPTIM_LEVEL = 2;
        else{
            std::cout << "Illegal optim arg: " << argv[1] << std::endl;
            return 3;
        }
        stream.open(argv[2]);
        cact_path = argv[2];
    }
    ANTLRInputStream input(stream);
    CACTLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CACTParser parser(&tokens);

    tree::ParseTree *tree = parser.compUnit();
    // std::cout << "---------------------------Print AST:-----------------------------" << std::endl;
    // std::cout << tree->toStringTree(&parser) << std::endl;

    //syntax
    tree::ParseTreeWalker::DEFAULT.walk(&syntax_analysis, tree);

    // std::cout << parser.getRuleNames()[19] << parser.getRuleNames()[20] << std::endl; 

    //semantic
    tree::ParseTreeWalker::DEFAULT.walk(&semantic_analysis, tree);

    #ifdef IR_gen
    ir_optim.optim();
    std::string file_name = cact_path.substr(cact_path.rfind('/')+1,cact_path.rfind('.')-cact_path.rfind('/')-1);
    std::string irc_path = std::string("IRC/")+file_name+std::string(".txt");
    std::ofstream irc_stream;
    irc_stream.open(irc_path);
    ir_optim.printIRC(irc_stream);

    #ifdef ASM_gen
    std::string asm_name = file_name + ".S";
    riscv_gen.Gen_All(asm_name);
    #endif

    #endif
    
    return 0;
}
