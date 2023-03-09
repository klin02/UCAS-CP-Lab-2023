#include <iostream>

#include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "HelloLexer.h"
#include "HelloParser.h"
#include "HelloVisitor.h"

using namespace antlr4;

class Analysis : public HelloVisitor {
public:
    antlrcpp::Any visitR(HelloParser::RContext *context) {
        visitChildren( context );
        
        std::cout << "enter rule [r]!" << std::endl;
        std::cout << "the ID is: " << context->ID()->getText().c_str() << std::endl;
        return nullptr;
    }

    antlrcpp::Any visitErrorNode(tree::ErrorNode * node) override {
        std::cout << "visit error node!" << std::endl;
        return nullptr;
    }
};

int main(int argc, const char* argv[]) {
  std::ifstream stream;
  stream.open("test.hello");

  ANTLRInputStream   input(stream);
  HelloLexer         lexer(&input);
  CommonTokenStream  tokens(&lexer);
  HelloParser        parser(&tokens);

  Analysis visitor;
  visitor.visit( parser.r() );

  return 0;
}