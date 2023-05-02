#pragma once

#include "antlr4-runtime.h"
#include "CACTListener.h"
#include "SymbolTable.h"

extern SymbolTable  symbol_table;
extern TypeUtils    typeutils;

#define Syntax_ERR   1
#define Semantic_ERR 2
#define Code_ERR     3   //代码编写中意料外的错误
class SemanticAnalysis: public CACTListener {
    public:
        scope_t *root_scope;
        scope_t *cur_scope;

        SemanticAnalysis(){}
        ~SemanticAnalysis(){}

        //添加内联函数声明
        void addBuiltinFunc(std::string func_name, int argc, cact_basety_t basety, cact_basety_t ret_type);

        //操作对象检查，非数组，并针对操作符检查类型
        //stmt_assign赋值同样需要满足上述判断
        void OperandCheck(cact_expr_ptr expr_ptr);

        void enterCompUnit(CACTParser::CompUnitContext *ctx) override;
        void exitCompUnit(CACTParser::CompUnitContext *ctx) override;

        void enterDecl(CACTParser::DeclContext *ctx) override;
        void exitDecl(CACTParser::DeclContext *ctx) override;

        void enterConstDecl(CACTParser::ConstDeclContext *ctx) override;
        void exitConstDecl(CACTParser::ConstDeclContext *ctx) override;

        void enterBType(CACTParser::BTypeContext *ctx) override;
        void exitBType(CACTParser::BTypeContext *ctx) override;

        void enterArrayDims(CACTParser::ArrayDimsContext *ctx) override;
        void exitArrayDims(CACTParser::ArrayDimsContext *ctx) override;

        void enterConstDef(CACTParser::ConstDefContext *ctx) override;
        void exitConstDef(CACTParser::ConstDefContext *ctx) override;

        void enterConstInitVal(CACTParser::ConstInitValContext *ctx) override;
        void exitConstInitVal(CACTParser::ConstInitValContext *ctx) override;

        void enterVarDecl(CACTParser::VarDeclContext *ctx) override;
        void exitVarDecl(CACTParser::VarDeclContext *ctx) override;

        void enterVarDef(CACTParser::VarDefContext *ctx) override;
        void exitVarDef(CACTParser::VarDefContext *ctx) override;

        void enterFuncDef(CACTParser::FuncDefContext *ctx) override;
        void exitFuncDef(CACTParser::FuncDefContext *ctx) override;

        void enterFuncType(CACTParser::FuncTypeContext *ctx) override;
        void exitFuncType(CACTParser::FuncTypeContext *ctx) override;

        void enterFuncFParam(CACTParser::FuncFParamContext *ctx) override;
        void exitFuncFParam(CACTParser::FuncFParamContext *ctx) override;

        void enterBlock(CACTParser::BlockContext *ctx) override;
        void exitBlock(CACTParser::BlockContext *ctx) override;

        void enterStmt_assign(CACTParser::Stmt_assignContext *ctx) override;
        void exitStmt_assign(CACTParser::Stmt_assignContext *ctx) override;

        void enterStmt_exp(CACTParser::Stmt_expContext *ctx) override;
        void exitStmt_exp(CACTParser::Stmt_expContext *ctx) override;

        void enterStmt_block(CACTParser::Stmt_blockContext *ctx) override;
        void exitStmt_block(CACTParser::Stmt_blockContext *ctx) override;

        void enterStmt_if(CACTParser::Stmt_ifContext *ctx) override;
        void exitStmt_if(CACTParser::Stmt_ifContext *ctx) override;

        void enterStmt_while(CACTParser::Stmt_whileContext *ctx) override;
        void exitStmt_while(CACTParser::Stmt_whileContext *ctx) override;

        void enterStmt_bcr(CACTParser::Stmt_bcrContext *ctx) override;
        void exitStmt_bcr(CACTParser::Stmt_bcrContext *ctx) override;

        void enterExp(CACTParser::ExpContext *ctx) override;
        void exitExp(CACTParser::ExpContext *ctx) override;

        void enterConstExp(CACTParser::ConstExpContext *ctx) override;
        void exitConstExp(CACTParser::ConstExpContext *ctx) override;

        void enterCond(CACTParser::CondContext *ctx) override;
        void exitCond(CACTParser::CondContext *ctx) override;

        void enterLVal(CACTParser::LValContext *ctx) override;
        void exitLVal(CACTParser::LValContext *ctx) override;

        void enterPrimaryExp(CACTParser::PrimaryExpContext *ctx) override;
        void exitPrimaryExp(CACTParser::PrimaryExpContext *ctx) override;

        void enterNumber(CACTParser::NumberContext *ctx) override;
        void exitNumber(CACTParser::NumberContext *ctx) override;

        void enterUnaryExp(CACTParser::UnaryExpContext *ctx) override;
        void exitUnaryExp(CACTParser::UnaryExpContext *ctx) override;

        void enterUnaryOp(CACTParser::UnaryOpContext *ctx) override;
        void exitUnaryOp(CACTParser::UnaryOpContext *ctx) override;

        void enterFuncRParams(CACTParser::FuncRParamsContext *ctx) override;
        void exitFuncRParams(CACTParser::FuncRParamsContext *ctx) override;

        void enterMulExp(CACTParser::MulExpContext *ctx) override;
        void exitMulExp(CACTParser::MulExpContext *ctx) override;

        void enterMulOp(CACTParser::MulOpContext *ctx) override;
        void exitMulOp(CACTParser::MulOpContext *ctx) override;

        void enterAddExp(CACTParser::AddExpContext *ctx) override;
        void exitAddExp(CACTParser::AddExpContext *ctx) override;

        void enterAddOp(CACTParser::AddOpContext *ctx) override;
        void exitAddOp(CACTParser::AddOpContext *ctx) override;

        void enterRelExp(CACTParser::RelExpContext *ctx) override;
        void exitRelExp(CACTParser::RelExpContext *ctx) override;

        void enterRelOp(CACTParser::RelOpContext *ctx) override;
        void exitRelOp(CACTParser::RelOpContext *ctx) override;

        void enterEqExp(CACTParser::EqExpContext *ctx) override;
        void exitEqExp(CACTParser::EqExpContext *ctx) override;

        void enterEqOp(CACTParser::EqOpContext *ctx) override;
        void exitEqOp(CACTParser::EqOpContext *ctx) override;

        void enterLAndExp(CACTParser::LAndExpContext *ctx) override;
        void exitLAndExp(CACTParser::LAndExpContext *ctx) override;

        void enterLOrExp(CACTParser::LOrExpContext *ctx) override;
        void exitLOrExp(CACTParser::LOrExpContext *ctx) override;

        void enterEveryRule(antlr4::ParserRuleContext * ctx) override;
        void exitEveryRule(antlr4::ParserRuleContext * ctx) override;
        void visitTerminal(antlr4::tree::TerminalNode * node) override;
        void visitErrorNode(antlr4::tree::ErrorNode * node) override;

};