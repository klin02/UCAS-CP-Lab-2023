
    #include <vector>
    #include <string>


// Generated from CACT.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "CACTParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CACTParser.
 */
class  CACTVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CACTParser.
   */
    virtual antlrcpp::Any visitCompUnit(CACTParser::CompUnitContext *context) = 0;

    virtual antlrcpp::Any visitDecl(CACTParser::DeclContext *context) = 0;

    virtual antlrcpp::Any visitConstDecl(CACTParser::ConstDeclContext *context) = 0;

    virtual antlrcpp::Any visitBType(CACTParser::BTypeContext *context) = 0;

    virtual antlrcpp::Any visitConstDef(CACTParser::ConstDefContext *context) = 0;

    virtual antlrcpp::Any visitConstInitVal(CACTParser::ConstInitValContext *context) = 0;

    virtual antlrcpp::Any visitVarDecl(CACTParser::VarDeclContext *context) = 0;

    virtual antlrcpp::Any visitVarDef(CACTParser::VarDefContext *context) = 0;

    virtual antlrcpp::Any visitFuncDef(CACTParser::FuncDefContext *context) = 0;

    virtual antlrcpp::Any visitFuncType(CACTParser::FuncTypeContext *context) = 0;

    virtual antlrcpp::Any visitFuncFParams(CACTParser::FuncFParamsContext *context) = 0;

    virtual antlrcpp::Any visitFuncFParam(CACTParser::FuncFParamContext *context) = 0;

    virtual antlrcpp::Any visitBlock(CACTParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitBlockItem(CACTParser::BlockItemContext *context) = 0;

    virtual antlrcpp::Any visitStmt(CACTParser::StmtContext *context) = 0;

    virtual antlrcpp::Any visitExp(CACTParser::ExpContext *context) = 0;

    virtual antlrcpp::Any visitConstExp(CACTParser::ConstExpContext *context) = 0;

    virtual antlrcpp::Any visitCond(CACTParser::CondContext *context) = 0;

    virtual antlrcpp::Any visitLVal(CACTParser::LValContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExp(CACTParser::PrimaryExpContext *context) = 0;

    virtual antlrcpp::Any visitNumber(CACTParser::NumberContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExp(CACTParser::UnaryExpContext *context) = 0;

    virtual antlrcpp::Any visitFuncRParams(CACTParser::FuncRParamsContext *context) = 0;

    virtual antlrcpp::Any visitMulExp(CACTParser::MulExpContext *context) = 0;

    virtual antlrcpp::Any visitAddExp(CACTParser::AddExpContext *context) = 0;

    virtual antlrcpp::Any visitRelExp(CACTParser::RelExpContext *context) = 0;

    virtual antlrcpp::Any visitEqExp(CACTParser::EqExpContext *context) = 0;

    virtual antlrcpp::Any visitLAndExp(CACTParser::LAndExpContext *context) = 0;

    virtual antlrcpp::Any visitLOrExp(CACTParser::LOrExpContext *context) = 0;


};

