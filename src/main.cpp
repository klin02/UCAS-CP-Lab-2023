#include <iostream>

#include "antlr4-runtime.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTListener.h"

#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "SemanticAnalysis.h"

using namespace antlr4;

SyntaxAnalysis      syntax_analysis;
SymbolTable         symbol_table;
TypeUtils           typeutils;
SemanticAnalysis    semantic_analysis;
int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);
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
    std::string cact_path = argv[1];
    //substr(start_pos,len)
    std::string file_name = cact_path.substr(cact_path.rfind('/')+1,cact_path.rfind('.cact')-cact_path.rfind('/'));
    // std::string file_name2 = cact_path.substr(cact_path.rfind('/')+1,cact_path.find('.cact'));

    // std::cout << "----------------------------IR Code: ------------------------------" << std::endl;
    // std::cout <<file_name <<" " <<file_name2 << cact_path.find('.cact')<< std::endl;
    std::string irc_path = std::string("IRC/")+file_name+std::string(".txt");
    std::ofstream irc_stream;
    irc_stream.open(irc_path);
    semantic_analysis.printIRC(irc_stream);
    #endif
    
    return 0;
}
