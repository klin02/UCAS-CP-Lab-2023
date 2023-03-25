#include <iostream>

#include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"

using namespace antlr4;

class Analysis : public CACTVisitor {
public:
    antlrcpp::Any visitR(CACTParser::RContext *context) {
        visitChildren( context );

        std::cout << "enter rule [r]!" << std::endl;
        std::cout << "the ID is: " << context->ID()->getText().c_str() << std::endl;
        return nullptr;
    }

    antlrcpp::Any visitErrorNode(tree::ErrorNode * node) override {
        std::cout << "visit error node!" << std::endl;
        exit(1);
        return nullptr;
    }
};

int main(int argc, const char* argv[]) {
  std::ifstream stream;
//   stream.open("test.CACT");
  stream.open(argv[1]);

  ANTLRInputStream   input(stream);
  CACTLexer          lexer(&input);
  CommonTokenStream  tokens(&lexer);
  CACTParser         parser(&tokens);

  Analysis visitor;
  visitor.visit( parser.r() );

  return 0;
}