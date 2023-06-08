#pragma once

#include "antlr4-runtime.h"
#include "CACTListener.h"
#include "SymbolTable.h"
#include "cact_types.h"

extern SymbolTable  symbol_table;
extern TypeUtils    typeutils;

#define Syntax_ERR   1
#define Semantic_ERR 2
#define Code_ERR     3   //代码编写中意料外的错误

#ifdef IR_gen
#define TEMP_PREFIX         "%"
#define OFFSET_INFIX        ">"
#define ARRAY_PLACEHOLDER   "$"
#define IMM_PREFIX          "#"
#define LABEL_PREFIX        "L"
#define GVAR_PREFIX         "@"
#define LVAR_PREFIX         "^"
#endif

class SemanticAnalysis: public CACTListener {
    public:
        scope_t *cur_scope;

        #ifdef IR_gen
        std::vector <IR_code_t> IRC_array;
        size_t label_cnt=0;
        // size_t end_label_cnt = 0;
        
        size_t len_from_type(cact_type_t type){
            if(type.arrdims.size()==0){
                return 1;
            }
            else{
                size_t product = 1;
                for(int dim: type.arrdims){
                    product *= dim;
                }
                return product;
            }
        }

        std::vector<IR_temp_t> Temp_array;
        std::string newTemp(cact_basety_t basety, bool is_const=false, size_t length=1){
            std::string temp_name = TEMP_PREFIX + std::to_string(Temp_array.size());
            Temp_array.push_back((IR_temp_t){.basety=basety,.is_const=is_const,.length=length});
            return temp_name;
        }

        std::vector<IR_temp_t> Gvar_array;
        std::string newGvar(cact_basety_t basety, bool is_const=false, size_t length=1){
            std::string gvar_name = GVAR_PREFIX + std::to_string(Gvar_array.size());
            Gvar_array.push_back((IR_temp_t){.basety=basety,.is_const=is_const,.length=length});
            return gvar_name;
        }

        std::vector<IR_temp_t> Lvar_array;
        std::string newLvar(cact_basety_t basety, bool is_const=false, size_t length=1){
            std::string lvar_name = LVAR_PREFIX + std::to_string(Lvar_array.size());
            Lvar_array.push_back((IR_temp_t){.basety=basety,.is_const=is_const,.length=length});
            return lvar_name;
        }

        std::string newLabel(){
            std::string label_name = LABEL_PREFIX + std::to_string(label_cnt);
            label_cnt++;
            return label_name;
        }

        //缺省参数，可以从左到右写参数，省略后面的部分
        void addIRC(IR_op_t IRop,cact_basety_t basety=BTY_UNKNOWN,std::string result="",std::string arg1="",std::string arg2=""){
            IRC_array.push_back((IR_code_t){IRop,basety,result,arg1,arg2});
        }

        //stmt进入和退出模板，用于处理进入添加in_label，退出跳至out_label
        template <typename T1>
        void enterStmt(T1 *ctx);
        template <typename T1>
        void exitStmt(T1 *ctx);

        void printIRC(std::ofstream &outfile){
            outfile << std::setw(10) << "IRop"   << '|' 
                    << std::setw(10) << "Basety" << '|' 
                    << std::setw(10) << "result" << '|' 
                    << std::setw(10) << "arg1"   << '|' 
                    << std::setw(10) << "arg2"   << '|' << std::endl;
            for(auto IRC = IRC_array.begin(); IRC!= IRC_array.end(); IRC++) {
                outfile << std::setw(10) << (typeutils.IRop_to_str)[IRC->IRop]      << '|' 
                        << std::setw(10) << (typeutils.basety_to_str)[IRC->basety]  << '|' 
                        << std::setw(10) << IRC->result << '|' 
                        << std::setw(10) << IRC->arg1   << '|' 
                        << std::setw(10) << IRC->arg2   << '|'<< std::endl;
            }
        }
        #endif

        //添加内联函数声明
        void addBuiltinFunc(std::string func_name, int argc, cact_basety_t basety, cact_basety_t ret_type);

        //操作对象检查，非数组，并针对操作符检查类型
        //stmt_assign赋值同样需要满足上述判断
        void OperandCheck(cact_expr_ptr expr_ptr);

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

        void enterLab(CACTParser::LabContext *ctx) override;
        void exitLab(CACTParser::LabContext *ctx) override;
        
        void enterGo(CACTParser::GoContext *ctx) override;
        void exitGo(CACTParser::GoContext *ctx) override;

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