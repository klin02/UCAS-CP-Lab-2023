
    #include "cact_types.h"
    #include "SymbolTable.h"
    #include <vector>
    #include <string>


// Generated from CACT.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "CACTListener.h"


/**
 * This class provides an empty implementation of CACTListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CACTBaseListener : public CACTListener {
public:

  virtual void enterCompUnit(CACTParser::CompUnitContext * /*ctx*/) override { }
  virtual void exitCompUnit(CACTParser::CompUnitContext * /*ctx*/) override { }

  virtual void enterDecl(CACTParser::DeclContext * /*ctx*/) override { }
  virtual void exitDecl(CACTParser::DeclContext * /*ctx*/) override { }

  virtual void enterConstDecl(CACTParser::ConstDeclContext * /*ctx*/) override { }
  virtual void exitConstDecl(CACTParser::ConstDeclContext * /*ctx*/) override { }

  virtual void enterBType(CACTParser::BTypeContext * /*ctx*/) override { }
  virtual void exitBType(CACTParser::BTypeContext * /*ctx*/) override { }

  virtual void enterArrayDims(CACTParser::ArrayDimsContext * /*ctx*/) override { }
  virtual void exitArrayDims(CACTParser::ArrayDimsContext * /*ctx*/) override { }

  virtual void enterConstDef(CACTParser::ConstDefContext * /*ctx*/) override { }
  virtual void exitConstDef(CACTParser::ConstDefContext * /*ctx*/) override { }

  virtual void enterConstInitVal(CACTParser::ConstInitValContext * /*ctx*/) override { }
  virtual void exitConstInitVal(CACTParser::ConstInitValContext * /*ctx*/) override { }

  virtual void enterVarDecl(CACTParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(CACTParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterVarDef(CACTParser::VarDefContext * /*ctx*/) override { }
  virtual void exitVarDef(CACTParser::VarDefContext * /*ctx*/) override { }

  virtual void enterFuncDef(CACTParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(CACTParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterFuncType(CACTParser::FuncTypeContext * /*ctx*/) override { }
  virtual void exitFuncType(CACTParser::FuncTypeContext * /*ctx*/) override { }

  virtual void enterFuncFParam(CACTParser::FuncFParamContext * /*ctx*/) override { }
  virtual void exitFuncFParam(CACTParser::FuncFParamContext * /*ctx*/) override { }

  virtual void enterLab(CACTParser::LabContext * /*ctx*/) override { }
  virtual void exitLab(CACTParser::LabContext * /*ctx*/) override { }

  virtual void enterGo(CACTParser::GoContext * /*ctx*/) override { }
  virtual void exitGo(CACTParser::GoContext * /*ctx*/) override { }

  virtual void enterBlock(CACTParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(CACTParser::BlockContext * /*ctx*/) override { }

  virtual void enterStmt_assign(CACTParser::Stmt_assignContext * /*ctx*/) override { }
  virtual void exitStmt_assign(CACTParser::Stmt_assignContext * /*ctx*/) override { }

  virtual void enterStmt_exp(CACTParser::Stmt_expContext * /*ctx*/) override { }
  virtual void exitStmt_exp(CACTParser::Stmt_expContext * /*ctx*/) override { }

  virtual void enterStmt_block(CACTParser::Stmt_blockContext * /*ctx*/) override { }
  virtual void exitStmt_block(CACTParser::Stmt_blockContext * /*ctx*/) override { }

  virtual void enterStmt_if(CACTParser::Stmt_ifContext * /*ctx*/) override { }
  virtual void exitStmt_if(CACTParser::Stmt_ifContext * /*ctx*/) override { }

  virtual void enterStmt_while(CACTParser::Stmt_whileContext * /*ctx*/) override { }
  virtual void exitStmt_while(CACTParser::Stmt_whileContext * /*ctx*/) override { }

  virtual void enterStmt_bcr(CACTParser::Stmt_bcrContext * /*ctx*/) override { }
  virtual void exitStmt_bcr(CACTParser::Stmt_bcrContext * /*ctx*/) override { }

  virtual void enterExp(CACTParser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(CACTParser::ExpContext * /*ctx*/) override { }

  virtual void enterConstExp(CACTParser::ConstExpContext * /*ctx*/) override { }
  virtual void exitConstExp(CACTParser::ConstExpContext * /*ctx*/) override { }

  virtual void enterCond(CACTParser::CondContext * /*ctx*/) override { }
  virtual void exitCond(CACTParser::CondContext * /*ctx*/) override { }

  virtual void enterLVal(CACTParser::LValContext * /*ctx*/) override { }
  virtual void exitLVal(CACTParser::LValContext * /*ctx*/) override { }

  virtual void enterPrimaryExp(CACTParser::PrimaryExpContext * /*ctx*/) override { }
  virtual void exitPrimaryExp(CACTParser::PrimaryExpContext * /*ctx*/) override { }

  virtual void enterNumber(CACTParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(CACTParser::NumberContext * /*ctx*/) override { }

  virtual void enterUnaryExp(CACTParser::UnaryExpContext * /*ctx*/) override { }
  virtual void exitUnaryExp(CACTParser::UnaryExpContext * /*ctx*/) override { }

  virtual void enterUnaryOp(CACTParser::UnaryOpContext * /*ctx*/) override { }
  virtual void exitUnaryOp(CACTParser::UnaryOpContext * /*ctx*/) override { }

  virtual void enterFuncRParams(CACTParser::FuncRParamsContext * /*ctx*/) override { }
  virtual void exitFuncRParams(CACTParser::FuncRParamsContext * /*ctx*/) override { }

  virtual void enterMulExp(CACTParser::MulExpContext * /*ctx*/) override { }
  virtual void exitMulExp(CACTParser::MulExpContext * /*ctx*/) override { }

  virtual void enterMulOp(CACTParser::MulOpContext * /*ctx*/) override { }
  virtual void exitMulOp(CACTParser::MulOpContext * /*ctx*/) override { }

  virtual void enterAddExp(CACTParser::AddExpContext * /*ctx*/) override { }
  virtual void exitAddExp(CACTParser::AddExpContext * /*ctx*/) override { }

  virtual void enterAddOp(CACTParser::AddOpContext * /*ctx*/) override { }
  virtual void exitAddOp(CACTParser::AddOpContext * /*ctx*/) override { }

  virtual void enterRelExp(CACTParser::RelExpContext * /*ctx*/) override { }
  virtual void exitRelExp(CACTParser::RelExpContext * /*ctx*/) override { }

  virtual void enterRelOp(CACTParser::RelOpContext * /*ctx*/) override { }
  virtual void exitRelOp(CACTParser::RelOpContext * /*ctx*/) override { }

  virtual void enterEqExp(CACTParser::EqExpContext * /*ctx*/) override { }
  virtual void exitEqExp(CACTParser::EqExpContext * /*ctx*/) override { }

  virtual void enterEqOp(CACTParser::EqOpContext * /*ctx*/) override { }
  virtual void exitEqOp(CACTParser::EqOpContext * /*ctx*/) override { }

  virtual void enterLAndExp(CACTParser::LAndExpContext * /*ctx*/) override { }
  virtual void exitLAndExp(CACTParser::LAndExpContext * /*ctx*/) override { }

  virtual void enterLOrExp(CACTParser::LOrExpContext * /*ctx*/) override { }
  virtual void exitLOrExp(CACTParser::LOrExpContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

