#include <iostream>

#include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"

using namespace antlr4;

class  Analysis : public CACTVisitor {
public:

  virtual antlrcpp::Any visitErrorNode(tree::ErrorNode *node) override{
    std::cout << "Error:" << node->getText() <<std::endl;
    exit(1);
  }
  virtual antlrcpp::Any visitCompUnit(CACTParser::CompUnitContext *ctx) override {
    return visitChildren(ctx);;
  }

  virtual antlrcpp::Any visitDecl(CACTParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstDecl(CACTParser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBType(CACTParser::BTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstDef(CACTParser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstInitVal(CACTParser::ConstInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDecl(CACTParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDef(CACTParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncDef(CACTParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncType(CACTParser::FuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncFParams(CACTParser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncFParam(CACTParser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(CACTParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlockItem(CACTParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmt(CACTParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExp(CACTParser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstExp(CACTParser::ConstExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCond(CACTParser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLVal(CACTParser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExp(CACTParser::PrimaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumber(CACTParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExp(CACTParser::UnaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncRParams(CACTParser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulExp(CACTParser::MulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddExp(CACTParser::AddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelExp(CACTParser::RelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEqExp(CACTParser::EqExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLAndExp(CACTParser::LAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLOrExp(CACTParser::LOrExpContext *ctx) override {
    return visitChildren(ctx);
  }
};


int main(int argc, const char* argv[]) {
  std::ifstream stream;
  stream.open(argv[1]);

  ANTLRInputStream   input(stream);
  CACTLexer          lexer(&input);
  CommonTokenStream  tokens(&lexer);
  CACTParser         parser(&tokens);

  tree::ParseTree *tree = parser.compUnit();

  std::cout << "---------------------------Print AST:-----------------------------" << std::endl;
  std::cout << tree->toStringTree(&parser) << std::endl;

  Analysis visitor;
  visitor.visit( tree );
  return 0;
}