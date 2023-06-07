#pragma once

#include "cact_types.h"
#include "IR.h"

//模板函数，提供公共逻辑
template <typename T1,typename T2>
void IR:: enterConst_Var_Decl(T1 *ctx,std::vector<T2*> def_list){}

template <typename T1>
void IR:: enterConst_Var_Def(T1 *ctx){}

//is_const区分constDef和varDef添加到变量表的不同类型
template <typename T1>
void IR:: exitConst_Var_Def(T1 *ctx, bool is_const){
    //区分全局变量和局部变量
    IR_op_t op;
    if(cur_scope == symbol_table.scope){
        op = G_ALLOC;
    }
    else{
        op = L_ALLOC;
    }

}

//二元表达式模板，处理形似 aExp -> bExp | aExp op bExp
//使用is_boolexp 区分Mul/Add 和 Rel/Eq/LAnd/LOr 的不同返回值类型
//注意RelExp还可能推导出BoolConst，考虑该分支后再应用模板
template <typename T1,typename T2, typename T3, typename T4>
void IR:: exitBinaryExp(T1 *ctx, T2 *aExp, T3 *op_ptr, T4 *bExp, bool is_boolexp){}

void IR:: enterCompUnit(CACTParser::CompUnitContext *ctx){}
void IR:: exitCompUnit(CACTParser::CompUnitContext *ctx){}

void IR:: enterDecl(CACTParser::DeclContext *ctx){}
void IR:: exitDecl(CACTParser::DeclContext *ctx){}

void IR:: enterConstDecl(CACTParser::ConstDeclContext *ctx){}
void IR:: exitConstDecl(CACTParser::ConstDeclContext *ctx){}

void IR:: enterBType(CACTParser::BTypeContext *ctx){}
void IR:: exitBType(CACTParser::BTypeContext *ctx){}

void IR:: enterArrayDims(CACTParser::ArrayDimsContext *ctx){}
void IR:: exitArrayDims(CACTParser::ArrayDimsContext *ctx){}

void IR:: enterConstDef(CACTParser::ConstDefContext *ctx){}
void IR:: exitConstDef(CACTParser::ConstDefContext *ctx){}

void IR:: enterConstInitVal(CACTParser::ConstInitValContext *ctx){}
void IR:: exitConstInitVal(CACTParser::ConstInitValContext *ctx){}

void IR:: enterVarDecl(CACTParser::VarDeclContext *ctx){}
void IR:: exitVarDecl(CACTParser::VarDeclContext *ctx){}

void IR:: enterVarDef(CACTParser::VarDefContext *ctx){}
void IR:: exitVarDef(CACTParser::VarDefContext *ctx){}

void IR:: enterFuncDef(CACTParser::FuncDefContext *ctx){}
void IR:: exitFuncDef(CACTParser::FuncDefContext *ctx){}

void IR:: enterFuncType(CACTParser::FuncTypeContext *ctx){}
void IR:: exitFuncType(CACTParser::FuncTypeContext *ctx){}

void IR:: enterFuncFParam(CACTParser::FuncFParamContext *ctx){}
void IR:: exitFuncFParam(CACTParser::FuncFParamContext *ctx){}

void IR:: enterBlock(CACTParser::BlockContext *ctx){}
void IR:: exitBlock(CACTParser::BlockContext *ctx){}

void IR:: enterStmt_assign(CACTParser::Stmt_assignContext *ctx){}
void IR:: exitStmt_assign(CACTParser::Stmt_assignContext *ctx){}

void IR:: enterStmt_exp(CACTParser::Stmt_expContext *ctx){}
void IR:: exitStmt_exp(CACTParser::Stmt_expContext *ctx){}

void IR:: enterStmt_block(CACTParser::Stmt_blockContext *ctx){}
void IR:: exitStmt_block(CACTParser::Stmt_blockContext *ctx){}

void IR:: enterStmt_if(CACTParser::Stmt_ifContext *ctx){}
void IR:: exitStmt_if(CACTParser::Stmt_ifContext *ctx){}

void IR:: enterStmt_while(CACTParser::Stmt_whileContext *ctx){}
void IR:: exitStmt_while(CACTParser::Stmt_whileContext *ctx){}

void IR:: enterStmt_bcr(CACTParser::Stmt_bcrContext *ctx){}
void IR:: exitStmt_bcr(CACTParser::Stmt_bcrContext *ctx){}

void IR:: enterExp(CACTParser::ExpContext *ctx){}
void IR:: exitExp(CACTParser::ExpContext *ctx){}

void IR:: enterConstExp(CACTParser::ConstExpContext *ctx){}
void IR:: exitConstExp(CACTParser::ConstExpContext *ctx){}

void IR:: enterCond(CACTParser::CondContext *ctx){}
void IR:: exitCond(CACTParser::CondContext *ctx){}

void IR:: enterLVal(CACTParser::LValContext *ctx){}
void IR:: exitLVal(CACTParser::LValContext *ctx){}

void IR:: enterPrimaryExp(CACTParser::PrimaryExpContext *ctx){}
void IR:: exitPrimaryExp(CACTParser::PrimaryExpContext *ctx){}

void IR:: enterNumber(CACTParser::NumberContext *ctx){}
void IR:: exitNumber(CACTParser::NumberContext *ctx){}

void IR:: enterUnaryExp(CACTParser::UnaryExpContext *ctx){}
void IR:: exitUnaryExp(CACTParser::UnaryExpContext *ctx){}

void IR:: enterUnaryOp(CACTParser::UnaryOpContext *ctx){}
void IR:: exitUnaryOp(CACTParser::UnaryOpContext *ctx){}

void IR:: enterFuncRParams(CACTParser::FuncRParamsContext *ctx){}
void IR:: exitFuncRParams(CACTParser::FuncRParamsContext *ctx){}

void IR:: enterMulExp(CACTParser::MulExpContext *ctx){}
void IR:: exitMulExp(CACTParser::MulExpContext *ctx){}

void IR:: enterMulOp(CACTParser::MulOpContext *ctx){}
void IR:: exitMulOp(CACTParser::MulOpContext *ctx){}

void IR:: enterAddExp(CACTParser::AddExpContext *ctx){}
void IR:: exitAddExp(CACTParser::AddExpContext *ctx){}

void IR:: enterAddOp(CACTParser::AddOpContext *ctx){}
void IR:: exitAddOp(CACTParser::AddOpContext *ctx){}

void IR:: enterRelExp(CACTParser::RelExpContext *ctx){}
void IR:: exitRelExp(CACTParser::RelExpContext *ctx){}

void IR:: enterRelOp(CACTParser::RelOpContext *ctx){}
void IR:: exitRelOp(CACTParser::RelOpContext *ctx){}

void IR:: enterEqExp(CACTParser::EqExpContext *ctx){}
void IR:: exitEqExp(CACTParser::EqExpContext *ctx){}

void IR:: enterEqOp(CACTParser::EqOpContext *ctx){}
void IR:: exitEqOp(CACTParser::EqOpContext *ctx){}

void IR:: enterLAndExp(CACTParser::LAndExpContext *ctx){}
void IR:: exitLAndExp(CACTParser::LAndExpContext *ctx){}

void IR:: enterLOrExp(CACTParser::LOrExpContext *ctx){}
void IR:: exitLOrExp(CACTParser::LOrExpContext *ctx){}