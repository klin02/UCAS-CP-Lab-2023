#include <iostream>
#include <string.h>

#include "antlr4-runtime.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTListener.h"

#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"
#include "RiscvGen.h"

using namespace antlr4;

int                 OPTIM_LEVEL;

SyntaxAnalysis      syntax_analysis;
SymbolTable         symbol_table;
TypeUtils           typeutils;
SemanticAnalysis    semantic_analysis;
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
        else if(argv[1]=="-O1")
            OPTIM_LEVEL = 1;
        else if(argv[1]=="-O2")
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
    //substr(start_pos,len)
    std::string file_name = cact_path.substr(cact_path.rfind('/')+1,cact_path.rfind('.')-cact_path.rfind('/')-1) + ".S";

    // std::cout << "----------------------------IR Code: ------------------------------" << std::endl;
    // std::cout <<file_name <<" " <<file_name2 << cact_path.find('.cact')<< std::endl;
    std::string irc_path = std::string("IRC/")+file_name+std::string(".txt");
    std::ofstream irc_stream;
    irc_stream.open(irc_path);
    semantic_analysis.printIRC(irc_stream);

    #ifdef ASM_gen
    riscv_gen.Gen_All(file_name);
    #endif

    #endif
    
    return 0;
}
