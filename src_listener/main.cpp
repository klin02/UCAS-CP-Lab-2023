#include <iostream>

#include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTListener.h"


using namespace antlr4;
using namespace antlr4::tree;

class Analysis : public antlr4::tree::ParseTreeListener {
public:
    virtual void enterEveryRule(ParserRuleContext* ctx) override {}
    virtual void visitTerminal(tree::TerminalNode* node) override {}
    virtual void visitErrorNode(tree::ErrorNode* node) override {exit(1);}
    virtual void exitEveryRule(ParserRuleContext* ctx) override {}
};

int main(int argc, const char* argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);
    ANTLRInputStream input(stream);
    CACTLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CACTParser parser(&tokens);

    tree::ParseTree *tree = parser.compUnit();

    std::cout << "---------------------------Print AST:-----------------------------" << std::endl;
    std::cout << tree->toStringTree(&parser) << std::endl;

    Analysis listener;
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    return 0;
}
