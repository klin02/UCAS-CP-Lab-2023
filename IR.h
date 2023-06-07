/*
* | FUNC_BEGIN | name | 
* | LD | res | type | base | offset | 
* | ST | res | type
*/

#pragma once 

#include "antlr4-runtime.h"
#include "CACTListener.h"

#include "cact_types.h"
#include "SymbolTable.h"

#include <vector>

#define TEMP_PREFIX "%"

extern SymbolTable  symbol_table;
extern TypeUtils    typeutils;

typedef enum{
    OP_UNKNOWN,
    FUNC_BEGIN,
    FUNC_END,
    PARAM,
    CALL,
    RETURN,
    LD,
    ST,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    AND,
    OR,
    NEG,
    NOT,
    BEQ,
    BNE,
    BLT,
    BGE,
    J,
    G_ALLOC,    //全局变量声明
    L_ALLOC,    //局部变量声明
}IR_op_t;

typedef struct{
    IR_op_t op;
    std::string result;
    std::string arg1;
    std::string arg2;
    cact_basety_t basety;
}IR_code_t;

typedef struct{
    cact_basety_t basety;
}IR_temp_t;

class IR: public CACTBaseListener{
    public:
        scope_t *cur_scope;

        std::vector <IR_code_t> IRC_array;
        size_t stmt_cnt=0;
        
        std::vector<IR_temp_t*> Temp_array;
        std::string newTemp(cact_basety_t basety){
            std::string temp_name = TEMP_PREFIX + std::to_string(Temp_array.size());
            IR_temp_t temp_info = (IR_temp_t){.basety = basety};
            temp_array.push_back(temp_info);
            return temp_name;
        }

        void addIRC(IR_op_t op=OP_UNKNOWN,std::string result="",std::string arg1="",std::string arg2="",cact_basety_t basety=BTY_UNKNOWN){
            IRC_array.push_back(new IR_code_t{op,result,arg1,arg2,basety});
        }
        //模板函数，提供公共逻辑
        template <typename T1,typename T2>
        void enterConst_Var_Decl(T1 *ctx,std::vector<T2*> def_list);

        template <typename T1>
        void enterConst_Var_Def(T1 *ctx);

        //is_const区分constDef和varDef添加到变量表的不同类型
        template <typename T1>
        void exitConst_Var_Def(T1 *ctx, bool is_const);

        //二元表达式模板，处理形似 aExp -> bExp | aExp op bExp
        //使用is_boolexp 区分Mul/Add 和 Rel/Eq/LAnd/LOr 的不同返回值类型
        //注意RelExp还可能推导出BoolConst，考虑该分支后再应用模板
        template <typename T1,typename T2, typename T3, typename T4>
        void exitBinaryExp(T1 *ctx, T2 *aExp, T3 *op_ptr, T4 *bExp, bool is_boolexp);

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
};