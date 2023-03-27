#include <iostream>

#include "antlr4-runtime.h"
#include "tree/ErrorNode.h"

#include "CACTLexer.h"
#include "CACTParser.h"
#include "CACTVisitor.h"

using namespace antlr4;

class Analysis : public CACTVisitor {
public:
    antlrcpp::Any visitCompUnit(CACTParser::CompUnitContext *context) {
        visitChildren( context );

        // std::cout << "enter rule [r]!" << std::endl;
        // std::cout << "the ID is: " << context->ID()->getText().c_str() << std::endl;
        return nullptr;
    }

    antlrcpp::Any visitErrorNode(tree::ErrorNode * node) override {
        std::cout << "visit error node!" << std::endl;
        exit(1);
        return nullptr;
    }

    antlrcpp::Any visitDecl(CACTParser::DeclContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitConstDecl(CACTParser::ConstDeclContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitBType(CACTParser::BTypeContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitConstDef(CACTParser::ConstDefContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitConstInitVal(CACTParser::ConstInitValContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitVarDecl(CACTParser::VarDeclContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitVarDef(CACTParser::VarDefContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitFuncDef(CACTParser::FuncDefContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitFuncType(CACTParser::FuncTypeContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitFuncFParams(CACTParser::FuncFParamsContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitFuncFParam(CACTParser::FuncFParamContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitBlock(CACTParser::BlockContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitBlockItem(CACTParser::BlockItemContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitStmt(CACTParser::StmtContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitExp(CACTParser::ExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitConstExp(CACTParser::ConstExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitCond(CACTParser::CondContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitLVal(CACTParser::LValContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitPrimaryExp(CACTParser::PrimaryExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitNumber(CACTParser::NumberContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitUnaryExp(CACTParser::UnaryExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitFuncRParams(CACTParser::FuncRParamsContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitMulExp(CACTParser::MulExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitAddExp(CACTParser::AddExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitRelExp(CACTParser::RelExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitEqExp(CACTParser::EqExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitLAndExp(CACTParser::LAndExpContext *context) {visitChildren(context); return nullptr;}

    antlrcpp::Any visitLOrExp(CACTParser::LOrExpContext *context) {visitChildren(context); return nullptr;}
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
  visitor.visit( parser.compUnit() );

  std::cout << parser.compUnit()->toStringTree(&parser) << std::endl;
  return 0;
}