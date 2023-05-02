
    #include "cact_types.h"
    #include "SymbolTable.h"
    #include <vector>
    #include <string>


// Generated from CACT.g4 by ANTLR 4.8


#include "CACTListener.h"

#include "CACTParser.h"


using namespace antlrcpp;
using namespace antlr4;

CACTParser::CACTParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CACTParser::~CACTParser() {
  delete _interpreter;
}

std::string CACTParser::getGrammarFileName() const {
  return "CACT.g4";
}

const std::vector<std::string>& CACTParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CACTParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompUnitContext ------------------------------------------------------------------

CACTParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::CompUnitContext::EOF() {
  return getToken(CACTParser::EOF, 0);
}

std::vector<CACTParser::DeclContext *> CACTParser::CompUnitContext::decl() {
  return getRuleContexts<CACTParser::DeclContext>();
}

CACTParser::DeclContext* CACTParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<CACTParser::DeclContext>(i);
}

std::vector<CACTParser::FuncDefContext *> CACTParser::CompUnitContext::funcDef() {
  return getRuleContexts<CACTParser::FuncDefContext>();
}

CACTParser::FuncDefContext* CACTParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<CACTParser::FuncDefContext>(i);
}


size_t CACTParser::CompUnitContext::getRuleIndex() const {
  return CACTParser::RuleCompUnit;
}

void CACTParser::CompUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompUnit(this);
}

void CACTParser::CompUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompUnit(this);
}

CACTParser::CompUnitContext* CACTParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, CACTParser::RuleCompUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(68);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(66);
        decl();
        break;
      }

      case 2: {
        setState(67);
        funcDef();
        break;
      }

      }
      setState(70); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::CONST)
      | (1ULL << CACTParser::VOID)
      | (1ULL << CACTParser::INT)
      | (1ULL << CACTParser::BOOL)
      | (1ULL << CACTParser::FLOAT)
      | (1ULL << CACTParser::DOUBLE))) != 0));
    setState(72);
    match(CACTParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

CACTParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::ConstDeclContext* CACTParser::DeclContext::constDecl() {
  return getRuleContext<CACTParser::ConstDeclContext>(0);
}

CACTParser::VarDeclContext* CACTParser::DeclContext::varDecl() {
  return getRuleContext<CACTParser::VarDeclContext>(0);
}


size_t CACTParser::DeclContext::getRuleIndex() const {
  return CACTParser::RuleDecl;
}

void CACTParser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void CACTParser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}

CACTParser::DeclContext* CACTParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, CACTParser::RuleDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(74);
        constDecl();
        break;
      }

      case CACTParser::INT:
      case CACTParser::BOOL:
      case CACTParser::FLOAT:
      case CACTParser::DOUBLE: {
        enterOuterAlt(_localctx, 2);
        setState(75);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

CACTParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::ConstDeclContext::CONST() {
  return getToken(CACTParser::CONST, 0);
}

CACTParser::BTypeContext* CACTParser::ConstDeclContext::bType() {
  return getRuleContext<CACTParser::BTypeContext>(0);
}

std::vector<CACTParser::ConstDefContext *> CACTParser::ConstDeclContext::constDef() {
  return getRuleContexts<CACTParser::ConstDefContext>();
}

CACTParser::ConstDefContext* CACTParser::ConstDeclContext::constDef(size_t i) {
  return getRuleContext<CACTParser::ConstDefContext>(i);
}

tree::TerminalNode* CACTParser::ConstDeclContext::SEMICOLON() {
  return getToken(CACTParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> CACTParser::ConstDeclContext::COMMA() {
  return getTokens(CACTParser::COMMA);
}

tree::TerminalNode* CACTParser::ConstDeclContext::COMMA(size_t i) {
  return getToken(CACTParser::COMMA, i);
}


size_t CACTParser::ConstDeclContext::getRuleIndex() const {
  return CACTParser::RuleConstDecl;
}

void CACTParser::ConstDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDecl(this);
}

void CACTParser::ConstDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDecl(this);
}

CACTParser::ConstDeclContext* CACTParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, CACTParser::RuleConstDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(CACTParser::CONST);
    setState(79);
    bType();
    setState(80);
    constDef();
    setState(85);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(81);
      match(CACTParser::COMMA);
      setState(82);
      constDef();
      setState(87);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(88);
    match(CACTParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

CACTParser::BTypeContext::BTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::BTypeContext::INT() {
  return getToken(CACTParser::INT, 0);
}

tree::TerminalNode* CACTParser::BTypeContext::BOOL() {
  return getToken(CACTParser::BOOL, 0);
}

tree::TerminalNode* CACTParser::BTypeContext::FLOAT() {
  return getToken(CACTParser::FLOAT, 0);
}

tree::TerminalNode* CACTParser::BTypeContext::DOUBLE() {
  return getToken(CACTParser::DOUBLE, 0);
}


size_t CACTParser::BTypeContext::getRuleIndex() const {
  return CACTParser::RuleBType;
}

void CACTParser::BTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBType(this);
}

void CACTParser::BTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBType(this);
}

CACTParser::BTypeContext* CACTParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, CACTParser::RuleBType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::INT)
      | (1ULL << CACTParser::BOOL)
      | (1ULL << CACTParser::FLOAT)
      | (1ULL << CACTParser::DOUBLE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDimsContext ------------------------------------------------------------------

CACTParser::ArrayDimsContext::ArrayDimsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CACTParser::ArrayDimsContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::ArrayDimsContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::ArrayDimsContext::IntConst() {
  return getTokens(CACTParser::IntConst);
}

tree::TerminalNode* CACTParser::ArrayDimsContext::IntConst(size_t i) {
  return getToken(CACTParser::IntConst, i);
}

std::vector<tree::TerminalNode *> CACTParser::ArrayDimsContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::ArrayDimsContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}


size_t CACTParser::ArrayDimsContext::getRuleIndex() const {
  return CACTParser::RuleArrayDims;
}

void CACTParser::ArrayDimsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDims(this);
}

void CACTParser::ArrayDimsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDims(this);
}

CACTParser::ArrayDimsContext* CACTParser::arrayDims() {
  ArrayDimsContext *_localctx = _tracker.createInstance<ArrayDimsContext>(_ctx, getState());
  enterRule(_localctx, 8, CACTParser::RuleArrayDims);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(92);
      match(CACTParser::LeftBracket);
      setState(93);
      match(CACTParser::IntConst);
      setState(94);
      match(CACTParser::RightBracket);
      setState(99);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

CACTParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::ConstDefContext::Ident() {
  return getToken(CACTParser::Ident, 0);
}

CACTParser::ArrayDimsContext* CACTParser::ConstDefContext::arrayDims() {
  return getRuleContext<CACTParser::ArrayDimsContext>(0);
}

tree::TerminalNode* CACTParser::ConstDefContext::ASSIGN() {
  return getToken(CACTParser::ASSIGN, 0);
}

CACTParser::ConstInitValContext* CACTParser::ConstDefContext::constInitVal() {
  return getRuleContext<CACTParser::ConstInitValContext>(0);
}


size_t CACTParser::ConstDefContext::getRuleIndex() const {
  return CACTParser::RuleConstDef;
}

void CACTParser::ConstDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDef(this);
}

void CACTParser::ConstDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDef(this);
}

CACTParser::ConstDefContext* CACTParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 10, CACTParser::RuleConstDef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(CACTParser::Ident);
    setState(101);
    arrayDims();
    setState(102);
    match(CACTParser::ASSIGN);
    setState(103);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

CACTParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::ConstExpContext* CACTParser::ConstInitValContext::constExp() {
  return getRuleContext<CACTParser::ConstExpContext>(0);
}

tree::TerminalNode* CACTParser::ConstInitValContext::LeftBrace() {
  return getToken(CACTParser::LeftBrace, 0);
}

tree::TerminalNode* CACTParser::ConstInitValContext::RightBrace() {
  return getToken(CACTParser::RightBrace, 0);
}

std::vector<CACTParser::ConstInitValContext *> CACTParser::ConstInitValContext::constInitVal() {
  return getRuleContexts<CACTParser::ConstInitValContext>();
}

CACTParser::ConstInitValContext* CACTParser::ConstInitValContext::constInitVal(size_t i) {
  return getRuleContext<CACTParser::ConstInitValContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::ConstInitValContext::COMMA() {
  return getTokens(CACTParser::COMMA);
}

tree::TerminalNode* CACTParser::ConstInitValContext::COMMA(size_t i) {
  return getToken(CACTParser::COMMA, i);
}


size_t CACTParser::ConstInitValContext::getRuleIndex() const {
  return CACTParser::RuleConstInitVal;
}

void CACTParser::ConstInitValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstInitVal(this);
}

void CACTParser::ConstInitValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstInitVal(this);
}

CACTParser::ConstInitValContext* CACTParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 12, CACTParser::RuleConstInitVal);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(118);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::BoolConst:
      case CACTParser::IntConst:
      case CACTParser::FloatConst:
      case CACTParser::DoubleConst: {
        enterOuterAlt(_localctx, 1);
        setState(105);
        constExp();
        break;
      }

      case CACTParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(106);
        match(CACTParser::LeftBrace);
        setState(115);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << CACTParser::LeftBrace)
          | (1ULL << CACTParser::BoolConst)
          | (1ULL << CACTParser::IntConst)
          | (1ULL << CACTParser::FloatConst)
          | (1ULL << CACTParser::DoubleConst))) != 0)) {
          setState(107);
          constInitVal();
          setState(112);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == CACTParser::COMMA) {
            setState(108);
            match(CACTParser::COMMA);
            setState(109);
            constInitVal();
            setState(114);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(117);
        match(CACTParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

CACTParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::BTypeContext* CACTParser::VarDeclContext::bType() {
  return getRuleContext<CACTParser::BTypeContext>(0);
}

std::vector<CACTParser::VarDefContext *> CACTParser::VarDeclContext::varDef() {
  return getRuleContexts<CACTParser::VarDefContext>();
}

CACTParser::VarDefContext* CACTParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<CACTParser::VarDefContext>(i);
}

tree::TerminalNode* CACTParser::VarDeclContext::SEMICOLON() {
  return getToken(CACTParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> CACTParser::VarDeclContext::COMMA() {
  return getTokens(CACTParser::COMMA);
}

tree::TerminalNode* CACTParser::VarDeclContext::COMMA(size_t i) {
  return getToken(CACTParser::COMMA, i);
}


size_t CACTParser::VarDeclContext::getRuleIndex() const {
  return CACTParser::RuleVarDecl;
}

void CACTParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void CACTParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}

CACTParser::VarDeclContext* CACTParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, CACTParser::RuleVarDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    bType();
    setState(121);
    varDef();
    setState(126);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(122);
      match(CACTParser::COMMA);
      setState(123);
      varDef();
      setState(128);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(129);
    match(CACTParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

CACTParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::VarDefContext::Ident() {
  return getToken(CACTParser::Ident, 0);
}

CACTParser::ArrayDimsContext* CACTParser::VarDefContext::arrayDims() {
  return getRuleContext<CACTParser::ArrayDimsContext>(0);
}

tree::TerminalNode* CACTParser::VarDefContext::ASSIGN() {
  return getToken(CACTParser::ASSIGN, 0);
}

CACTParser::ConstInitValContext* CACTParser::VarDefContext::constInitVal() {
  return getRuleContext<CACTParser::ConstInitValContext>(0);
}


size_t CACTParser::VarDefContext::getRuleIndex() const {
  return CACTParser::RuleVarDef;
}

void CACTParser::VarDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDef(this);
}

void CACTParser::VarDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDef(this);
}

CACTParser::VarDefContext* CACTParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 16, CACTParser::RuleVarDef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    match(CACTParser::Ident);
    setState(132);
    arrayDims();
    setState(135);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::ASSIGN) {
      setState(133);
      match(CACTParser::ASSIGN);
      setState(134);
      constInitVal();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

CACTParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::FuncTypeContext* CACTParser::FuncDefContext::funcType() {
  return getRuleContext<CACTParser::FuncTypeContext>(0);
}

tree::TerminalNode* CACTParser::FuncDefContext::Ident() {
  return getToken(CACTParser::Ident, 0);
}

tree::TerminalNode* CACTParser::FuncDefContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

tree::TerminalNode* CACTParser::FuncDefContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

CACTParser::BlockContext* CACTParser::FuncDefContext::block() {
  return getRuleContext<CACTParser::BlockContext>(0);
}

std::vector<CACTParser::FuncFParamContext *> CACTParser::FuncDefContext::funcFParam() {
  return getRuleContexts<CACTParser::FuncFParamContext>();
}

CACTParser::FuncFParamContext* CACTParser::FuncDefContext::funcFParam(size_t i) {
  return getRuleContext<CACTParser::FuncFParamContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::FuncDefContext::COMMA() {
  return getTokens(CACTParser::COMMA);
}

tree::TerminalNode* CACTParser::FuncDefContext::COMMA(size_t i) {
  return getToken(CACTParser::COMMA, i);
}


size_t CACTParser::FuncDefContext::getRuleIndex() const {
  return CACTParser::RuleFuncDef;
}

void CACTParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void CACTParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}

CACTParser::FuncDefContext* CACTParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 18, CACTParser::RuleFuncDef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    funcType();
    setState(138);
    match(CACTParser::Ident);
    setState(139);
    match(CACTParser::LeftParen);
    setState(141);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::INT)
      | (1ULL << CACTParser::BOOL)
      | (1ULL << CACTParser::FLOAT)
      | (1ULL << CACTParser::DOUBLE))) != 0)) {
      setState(140);
      funcFParam();
    }
    setState(147);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(143);
      match(CACTParser::COMMA);
      setState(144);
      funcFParam();
      setState(149);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(150);
    match(CACTParser::RightParen);
    setState(151);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

CACTParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::FuncTypeContext::VOID() {
  return getToken(CACTParser::VOID, 0);
}

tree::TerminalNode* CACTParser::FuncTypeContext::INT() {
  return getToken(CACTParser::INT, 0);
}

tree::TerminalNode* CACTParser::FuncTypeContext::FLOAT() {
  return getToken(CACTParser::FLOAT, 0);
}

tree::TerminalNode* CACTParser::FuncTypeContext::DOUBLE() {
  return getToken(CACTParser::DOUBLE, 0);
}

tree::TerminalNode* CACTParser::FuncTypeContext::BOOL() {
  return getToken(CACTParser::BOOL, 0);
}


size_t CACTParser::FuncTypeContext::getRuleIndex() const {
  return CACTParser::RuleFuncType;
}

void CACTParser::FuncTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncType(this);
}

void CACTParser::FuncTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncType(this);
}

CACTParser::FuncTypeContext* CACTParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 20, CACTParser::RuleFuncType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::VOID)
      | (1ULL << CACTParser::INT)
      | (1ULL << CACTParser::BOOL)
      | (1ULL << CACTParser::FLOAT)
      | (1ULL << CACTParser::DOUBLE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

CACTParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::BTypeContext* CACTParser::FuncFParamContext::bType() {
  return getRuleContext<CACTParser::BTypeContext>(0);
}

tree::TerminalNode* CACTParser::FuncFParamContext::Ident() {
  return getToken(CACTParser::Ident, 0);
}

std::vector<tree::TerminalNode *> CACTParser::FuncFParamContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::FuncFParamContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::FuncFParamContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::FuncFParamContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::FuncFParamContext::IntConst() {
  return getTokens(CACTParser::IntConst);
}

tree::TerminalNode* CACTParser::FuncFParamContext::IntConst(size_t i) {
  return getToken(CACTParser::IntConst, i);
}


size_t CACTParser::FuncFParamContext::getRuleIndex() const {
  return CACTParser::RuleFuncFParam;
}

void CACTParser::FuncFParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncFParam(this);
}

void CACTParser::FuncFParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncFParam(this);
}

CACTParser::FuncFParamContext* CACTParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 22, CACTParser::RuleFuncFParam);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    bType();
    setState(156);
    match(CACTParser::Ident);
    setState(170);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::LeftBracket) {
      setState(157);
      match(CACTParser::LeftBracket);
      setState(159);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CACTParser::IntConst) {
        setState(158);
        match(CACTParser::IntConst);
      }
      setState(161);
      match(CACTParser::RightBracket);
      setState(167);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CACTParser::LeftBracket) {
        setState(162);
        match(CACTParser::LeftBracket);
        setState(163);
        match(CACTParser::IntConst);
        setState(164);
        match(CACTParser::RightBracket);
        setState(169);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

CACTParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::BlockContext::LeftBrace() {
  return getToken(CACTParser::LeftBrace, 0);
}

tree::TerminalNode* CACTParser::BlockContext::RightBrace() {
  return getToken(CACTParser::RightBrace, 0);
}

std::vector<CACTParser::DeclContext *> CACTParser::BlockContext::decl() {
  return getRuleContexts<CACTParser::DeclContext>();
}

CACTParser::DeclContext* CACTParser::BlockContext::decl(size_t i) {
  return getRuleContext<CACTParser::DeclContext>(i);
}

std::vector<CACTParser::StmtContext *> CACTParser::BlockContext::stmt() {
  return getRuleContexts<CACTParser::StmtContext>();
}

CACTParser::StmtContext* CACTParser::BlockContext::stmt(size_t i) {
  return getRuleContext<CACTParser::StmtContext>(i);
}


size_t CACTParser::BlockContext::getRuleIndex() const {
  return CACTParser::RuleBlock;
}

void CACTParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void CACTParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

CACTParser::BlockContext* CACTParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 24, CACTParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    match(CACTParser::LeftBrace);
    setState(177);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::LeftParen)
      | (1ULL << CACTParser::LeftBrace)
      | (1ULL << CACTParser::SEMICOLON)
      | (1ULL << CACTParser::CONST)
      | (1ULL << CACTParser::INT)
      | (1ULL << CACTParser::BOOL)
      | (1ULL << CACTParser::FLOAT)
      | (1ULL << CACTParser::DOUBLE)
      | (1ULL << CACTParser::IF)
      | (1ULL << CACTParser::WHILE)
      | (1ULL << CACTParser::BREAK)
      | (1ULL << CACTParser::CONTINUE)
      | (1ULL << CACTParser::RETURN)
      | (1ULL << CACTParser::ADD)
      | (1ULL << CACTParser::SUB)
      | (1ULL << CACTParser::NOT)
      | (1ULL << CACTParser::BoolConst)
      | (1ULL << CACTParser::Ident)
      | (1ULL << CACTParser::IntConst)
      | (1ULL << CACTParser::FloatConst)
      | (1ULL << CACTParser::DoubleConst))) != 0)) {
      setState(175);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CACTParser::CONST:
        case CACTParser::INT:
        case CACTParser::BOOL:
        case CACTParser::FLOAT:
        case CACTParser::DOUBLE: {
          setState(173);
          decl();
          break;
        }

        case CACTParser::LeftParen:
        case CACTParser::LeftBrace:
        case CACTParser::SEMICOLON:
        case CACTParser::IF:
        case CACTParser::WHILE:
        case CACTParser::BREAK:
        case CACTParser::CONTINUE:
        case CACTParser::RETURN:
        case CACTParser::ADD:
        case CACTParser::SUB:
        case CACTParser::NOT:
        case CACTParser::BoolConst:
        case CACTParser::Ident:
        case CACTParser::IntConst:
        case CACTParser::FloatConst:
        case CACTParser::DoubleConst: {
          setState(174);
          stmt();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(179);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(180);
    match(CACTParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

CACTParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CACTParser::StmtContext::getRuleIndex() const {
  return CACTParser::RuleStmt;
}

void CACTParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
  this->ret_type = ctx->ret_type;
}

//----------------- Stmt_ifContext ------------------------------------------------------------------

tree::TerminalNode* CACTParser::Stmt_ifContext::IF() {
  return getToken(CACTParser::IF, 0);
}

tree::TerminalNode* CACTParser::Stmt_ifContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

CACTParser::CondContext* CACTParser::Stmt_ifContext::cond() {
  return getRuleContext<CACTParser::CondContext>(0);
}

tree::TerminalNode* CACTParser::Stmt_ifContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

std::vector<CACTParser::StmtContext *> CACTParser::Stmt_ifContext::stmt() {
  return getRuleContexts<CACTParser::StmtContext>();
}

CACTParser::StmtContext* CACTParser::Stmt_ifContext::stmt(size_t i) {
  return getRuleContext<CACTParser::StmtContext>(i);
}

tree::TerminalNode* CACTParser::Stmt_ifContext::ELSE() {
  return getToken(CACTParser::ELSE, 0);
}

CACTParser::Stmt_ifContext::Stmt_ifContext(StmtContext *ctx) { copyFrom(ctx); }

void CACTParser::Stmt_ifContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_if(this);
}
void CACTParser::Stmt_ifContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_if(this);
}
//----------------- Stmt_blockContext ------------------------------------------------------------------

CACTParser::BlockContext* CACTParser::Stmt_blockContext::block() {
  return getRuleContext<CACTParser::BlockContext>(0);
}

CACTParser::Stmt_blockContext::Stmt_blockContext(StmtContext *ctx) { copyFrom(ctx); }

void CACTParser::Stmt_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_block(this);
}
void CACTParser::Stmt_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_block(this);
}
//----------------- Stmt_bcrContext ------------------------------------------------------------------

tree::TerminalNode* CACTParser::Stmt_bcrContext::SEMICOLON() {
  return getToken(CACTParser::SEMICOLON, 0);
}

tree::TerminalNode* CACTParser::Stmt_bcrContext::BREAK() {
  return getToken(CACTParser::BREAK, 0);
}

tree::TerminalNode* CACTParser::Stmt_bcrContext::CONTINUE() {
  return getToken(CACTParser::CONTINUE, 0);
}

tree::TerminalNode* CACTParser::Stmt_bcrContext::RETURN() {
  return getToken(CACTParser::RETURN, 0);
}

CACTParser::ExpContext* CACTParser::Stmt_bcrContext::exp() {
  return getRuleContext<CACTParser::ExpContext>(0);
}

CACTParser::Stmt_bcrContext::Stmt_bcrContext(StmtContext *ctx) { copyFrom(ctx); }

void CACTParser::Stmt_bcrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_bcr(this);
}
void CACTParser::Stmt_bcrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_bcr(this);
}
//----------------- Stmt_whileContext ------------------------------------------------------------------

tree::TerminalNode* CACTParser::Stmt_whileContext::WHILE() {
  return getToken(CACTParser::WHILE, 0);
}

tree::TerminalNode* CACTParser::Stmt_whileContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

CACTParser::CondContext* CACTParser::Stmt_whileContext::cond() {
  return getRuleContext<CACTParser::CondContext>(0);
}

tree::TerminalNode* CACTParser::Stmt_whileContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

CACTParser::StmtContext* CACTParser::Stmt_whileContext::stmt() {
  return getRuleContext<CACTParser::StmtContext>(0);
}

CACTParser::Stmt_whileContext::Stmt_whileContext(StmtContext *ctx) { copyFrom(ctx); }

void CACTParser::Stmt_whileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_while(this);
}
void CACTParser::Stmt_whileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_while(this);
}
//----------------- Stmt_assignContext ------------------------------------------------------------------

CACTParser::LValContext* CACTParser::Stmt_assignContext::lVal() {
  return getRuleContext<CACTParser::LValContext>(0);
}

tree::TerminalNode* CACTParser::Stmt_assignContext::ASSIGN() {
  return getToken(CACTParser::ASSIGN, 0);
}

CACTParser::ExpContext* CACTParser::Stmt_assignContext::exp() {
  return getRuleContext<CACTParser::ExpContext>(0);
}

tree::TerminalNode* CACTParser::Stmt_assignContext::SEMICOLON() {
  return getToken(CACTParser::SEMICOLON, 0);
}

CACTParser::Stmt_assignContext::Stmt_assignContext(StmtContext *ctx) { copyFrom(ctx); }

void CACTParser::Stmt_assignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_assign(this);
}
void CACTParser::Stmt_assignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_assign(this);
}
//----------------- Stmt_expContext ------------------------------------------------------------------

tree::TerminalNode* CACTParser::Stmt_expContext::SEMICOLON() {
  return getToken(CACTParser::SEMICOLON, 0);
}

CACTParser::ExpContext* CACTParser::Stmt_expContext::exp() {
  return getRuleContext<CACTParser::ExpContext>(0);
}

CACTParser::Stmt_expContext::Stmt_expContext(StmtContext *ctx) { copyFrom(ctx); }

void CACTParser::Stmt_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_exp(this);
}
void CACTParser::Stmt_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_exp(this);
}
CACTParser::StmtContext* CACTParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 26, CACTParser::RuleStmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(216);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<CACTParser::Stmt_assignContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(182);
      lVal();
      setState(183);
      match(CACTParser::ASSIGN);
      setState(184);
      exp();
      setState(185);
      match(CACTParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<CACTParser::Stmt_expContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(188);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CACTParser::LeftParen)
        | (1ULL << CACTParser::ADD)
        | (1ULL << CACTParser::SUB)
        | (1ULL << CACTParser::NOT)
        | (1ULL << CACTParser::BoolConst)
        | (1ULL << CACTParser::Ident)
        | (1ULL << CACTParser::IntConst)
        | (1ULL << CACTParser::FloatConst)
        | (1ULL << CACTParser::DoubleConst))) != 0)) {
        setState(187);
        exp();
      }
      setState(190);
      match(CACTParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<CACTParser::Stmt_blockContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(191);
      block();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<CACTParser::Stmt_ifContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(192);
      match(CACTParser::IF);
      setState(193);
      match(CACTParser::LeftParen);
      setState(194);
      cond();
      setState(195);
      match(CACTParser::RightParen);
      setState(196);
      stmt();
      setState(199);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
      case 1: {
        setState(197);
        match(CACTParser::ELSE);
        setState(198);
        stmt();
        break;
      }

      }
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<CACTParser::Stmt_whileContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(201);
      match(CACTParser::WHILE);
      setState(202);
      match(CACTParser::LeftParen);
      setState(203);
      cond();
      setState(204);
      match(CACTParser::RightParen);
      setState(205);
      stmt();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StmtContext *>(_tracker.createInstance<CACTParser::Stmt_bcrContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(213);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CACTParser::BREAK: {
          setState(207);
          match(CACTParser::BREAK);
          break;
        }

        case CACTParser::CONTINUE: {
          setState(208);
          match(CACTParser::CONTINUE);
          break;
        }

        case CACTParser::RETURN: {
          setState(209);
          match(CACTParser::RETURN);
          setState(211);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << CACTParser::LeftParen)
            | (1ULL << CACTParser::ADD)
            | (1ULL << CACTParser::SUB)
            | (1ULL << CACTParser::NOT)
            | (1ULL << CACTParser::BoolConst)
            | (1ULL << CACTParser::Ident)
            | (1ULL << CACTParser::IntConst)
            | (1ULL << CACTParser::FloatConst)
            | (1ULL << CACTParser::DoubleConst))) != 0)) {
            setState(210);
            exp();
          }
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(215);
      match(CACTParser::SEMICOLON);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

CACTParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::ExpContext::BoolConst() {
  return getToken(CACTParser::BoolConst, 0);
}

CACTParser::AddExpContext* CACTParser::ExpContext::addExp() {
  return getRuleContext<CACTParser::AddExpContext>(0);
}


size_t CACTParser::ExpContext::getRuleIndex() const {
  return CACTParser::RuleExp;
}

void CACTParser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void CACTParser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}

CACTParser::ExpContext* CACTParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 28, CACTParser::RuleExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(220);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::BoolConst: {
        enterOuterAlt(_localctx, 1);
        setState(218);
        match(CACTParser::BoolConst);
        break;
      }

      case CACTParser::LeftParen:
      case CACTParser::ADD:
      case CACTParser::SUB:
      case CACTParser::NOT:
      case CACTParser::Ident:
      case CACTParser::IntConst:
      case CACTParser::FloatConst:
      case CACTParser::DoubleConst: {
        enterOuterAlt(_localctx, 2);
        setState(219);
        addExp(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

CACTParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::NumberContext* CACTParser::ConstExpContext::number() {
  return getRuleContext<CACTParser::NumberContext>(0);
}

tree::TerminalNode* CACTParser::ConstExpContext::BoolConst() {
  return getToken(CACTParser::BoolConst, 0);
}


size_t CACTParser::ConstExpContext::getRuleIndex() const {
  return CACTParser::RuleConstExp;
}

void CACTParser::ConstExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstExp(this);
}

void CACTParser::ConstExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstExp(this);
}

CACTParser::ConstExpContext* CACTParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 30, CACTParser::RuleConstExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(224);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntConst:
      case CACTParser::FloatConst:
      case CACTParser::DoubleConst: {
        enterOuterAlt(_localctx, 1);
        setState(222);
        number();
        break;
      }

      case CACTParser::BoolConst: {
        enterOuterAlt(_localctx, 2);
        setState(223);
        match(CACTParser::BoolConst);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

CACTParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::LOrExpContext* CACTParser::CondContext::lOrExp() {
  return getRuleContext<CACTParser::LOrExpContext>(0);
}


size_t CACTParser::CondContext::getRuleIndex() const {
  return CACTParser::RuleCond;
}

void CACTParser::CondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCond(this);
}

void CACTParser::CondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCond(this);
}

CACTParser::CondContext* CACTParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 32, CACTParser::RuleCond);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(226);
    lOrExp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

CACTParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::LValContext::Ident() {
  return getToken(CACTParser::Ident, 0);
}

std::vector<tree::TerminalNode *> CACTParser::LValContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::LValContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<CACTParser::ExpContext *> CACTParser::LValContext::exp() {
  return getRuleContexts<CACTParser::ExpContext>();
}

CACTParser::ExpContext* CACTParser::LValContext::exp(size_t i) {
  return getRuleContext<CACTParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::LValContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::LValContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}


size_t CACTParser::LValContext::getRuleIndex() const {
  return CACTParser::RuleLVal;
}

void CACTParser::LValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLVal(this);
}

void CACTParser::LValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLVal(this);
}

CACTParser::LValContext* CACTParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 34, CACTParser::RuleLVal);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(228);
    match(CACTParser::Ident);
    setState(235);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(229);
        match(CACTParser::LeftBracket);
        setState(230);
        exp();
        setState(231);
        match(CACTParser::RightBracket); 
      }
      setState(237);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

CACTParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::NumberContext* CACTParser::PrimaryExpContext::number() {
  return getRuleContext<CACTParser::NumberContext>(0);
}

CACTParser::LValContext* CACTParser::PrimaryExpContext::lVal() {
  return getRuleContext<CACTParser::LValContext>(0);
}

tree::TerminalNode* CACTParser::PrimaryExpContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

CACTParser::ExpContext* CACTParser::PrimaryExpContext::exp() {
  return getRuleContext<CACTParser::ExpContext>(0);
}

tree::TerminalNode* CACTParser::PrimaryExpContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}


size_t CACTParser::PrimaryExpContext::getRuleIndex() const {
  return CACTParser::RulePrimaryExp;
}

void CACTParser::PrimaryExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExp(this);
}

void CACTParser::PrimaryExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExp(this);
}

CACTParser::PrimaryExpContext* CACTParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 36, CACTParser::RulePrimaryExp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(244);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::IntConst:
      case CACTParser::FloatConst:
      case CACTParser::DoubleConst: {
        enterOuterAlt(_localctx, 1);
        setState(238);
        number();
        break;
      }

      case CACTParser::Ident: {
        enterOuterAlt(_localctx, 2);
        setState(239);
        lVal();
        break;
      }

      case CACTParser::LeftParen: {
        enterOuterAlt(_localctx, 3);
        setState(240);
        match(CACTParser::LeftParen);
        setState(241);
        exp();
        setState(242);
        match(CACTParser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

CACTParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::NumberContext::IntConst() {
  return getToken(CACTParser::IntConst, 0);
}

tree::TerminalNode* CACTParser::NumberContext::DoubleConst() {
  return getToken(CACTParser::DoubleConst, 0);
}

tree::TerminalNode* CACTParser::NumberContext::FloatConst() {
  return getToken(CACTParser::FloatConst, 0);
}


size_t CACTParser::NumberContext::getRuleIndex() const {
  return CACTParser::RuleNumber;
}

void CACTParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void CACTParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

CACTParser::NumberContext* CACTParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 38, CACTParser::RuleNumber);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::IntConst)
      | (1ULL << CACTParser::FloatConst)
      | (1ULL << CACTParser::DoubleConst))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

CACTParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::PrimaryExpContext* CACTParser::UnaryExpContext::primaryExp() {
  return getRuleContext<CACTParser::PrimaryExpContext>(0);
}

CACTParser::UnaryOpContext* CACTParser::UnaryExpContext::unaryOp() {
  return getRuleContext<CACTParser::UnaryOpContext>(0);
}

CACTParser::UnaryExpContext* CACTParser::UnaryExpContext::unaryExp() {
  return getRuleContext<CACTParser::UnaryExpContext>(0);
}

tree::TerminalNode* CACTParser::UnaryExpContext::Ident() {
  return getToken(CACTParser::Ident, 0);
}

tree::TerminalNode* CACTParser::UnaryExpContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

tree::TerminalNode* CACTParser::UnaryExpContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

CACTParser::FuncRParamsContext* CACTParser::UnaryExpContext::funcRParams() {
  return getRuleContext<CACTParser::FuncRParamsContext>(0);
}


size_t CACTParser::UnaryExpContext::getRuleIndex() const {
  return CACTParser::RuleUnaryExp;
}

void CACTParser::UnaryExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExp(this);
}

void CACTParser::UnaryExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExp(this);
}

CACTParser::UnaryExpContext* CACTParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 40, CACTParser::RuleUnaryExp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(258);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(248);
      primaryExp();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(249);
      unaryOp();
      setState(250);
      unaryExp();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(252);
      match(CACTParser::Ident);
      setState(253);
      match(CACTParser::LeftParen);
      setState(255);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CACTParser::LeftParen)
        | (1ULL << CACTParser::ADD)
        | (1ULL << CACTParser::SUB)
        | (1ULL << CACTParser::NOT)
        | (1ULL << CACTParser::BoolConst)
        | (1ULL << CACTParser::Ident)
        | (1ULL << CACTParser::IntConst)
        | (1ULL << CACTParser::FloatConst)
        | (1ULL << CACTParser::DoubleConst))) != 0)) {
        setState(254);
        funcRParams();
      }
      setState(257);
      match(CACTParser::RightParen);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOpContext ------------------------------------------------------------------

CACTParser::UnaryOpContext::UnaryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::UnaryOpContext::ADD() {
  return getToken(CACTParser::ADD, 0);
}

tree::TerminalNode* CACTParser::UnaryOpContext::SUB() {
  return getToken(CACTParser::SUB, 0);
}

tree::TerminalNode* CACTParser::UnaryOpContext::NOT() {
  return getToken(CACTParser::NOT, 0);
}


size_t CACTParser::UnaryOpContext::getRuleIndex() const {
  return CACTParser::RuleUnaryOp;
}

void CACTParser::UnaryOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOp(this);
}

void CACTParser::UnaryOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOp(this);
}

CACTParser::UnaryOpContext* CACTParser::unaryOp() {
  UnaryOpContext *_localctx = _tracker.createInstance<UnaryOpContext>(_ctx, getState());
  enterRule(_localctx, 42, CACTParser::RuleUnaryOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::ADD)
      | (1ULL << CACTParser::SUB)
      | (1ULL << CACTParser::NOT))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

CACTParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::ExpContext *> CACTParser::FuncRParamsContext::exp() {
  return getRuleContexts<CACTParser::ExpContext>();
}

CACTParser::ExpContext* CACTParser::FuncRParamsContext::exp(size_t i) {
  return getRuleContext<CACTParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::FuncRParamsContext::COMMA() {
  return getTokens(CACTParser::COMMA);
}

tree::TerminalNode* CACTParser::FuncRParamsContext::COMMA(size_t i) {
  return getToken(CACTParser::COMMA, i);
}


size_t CACTParser::FuncRParamsContext::getRuleIndex() const {
  return CACTParser::RuleFuncRParams;
}

void CACTParser::FuncRParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncRParams(this);
}

void CACTParser::FuncRParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncRParams(this);
}

CACTParser::FuncRParamsContext* CACTParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 44, CACTParser::RuleFuncRParams);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    exp();
    setState(267);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(263);
      match(CACTParser::COMMA);
      setState(264);
      exp();
      setState(269);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

CACTParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::UnaryExpContext* CACTParser::MulExpContext::unaryExp() {
  return getRuleContext<CACTParser::UnaryExpContext>(0);
}

CACTParser::MulExpContext* CACTParser::MulExpContext::mulExp() {
  return getRuleContext<CACTParser::MulExpContext>(0);
}

CACTParser::MulOpContext* CACTParser::MulExpContext::mulOp() {
  return getRuleContext<CACTParser::MulOpContext>(0);
}


size_t CACTParser::MulExpContext::getRuleIndex() const {
  return CACTParser::RuleMulExp;
}

void CACTParser::MulExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExp(this);
}

void CACTParser::MulExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExp(this);
}


CACTParser::MulExpContext* CACTParser::mulExp() {
   return mulExp(0);
}

CACTParser::MulExpContext* CACTParser::mulExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CACTParser::MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, parentState);
  CACTParser::MulExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CACTParser::RuleMulExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(271);
    unaryExp();
    _ctx->stop = _input->LT(-1);
    setState(279);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulExp);
        setState(273);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(274);
        mulOp();
        setState(275);
        unaryExp(); 
      }
      setState(281);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MulOpContext ------------------------------------------------------------------

CACTParser::MulOpContext::MulOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::MulOpContext::MUL() {
  return getToken(CACTParser::MUL, 0);
}

tree::TerminalNode* CACTParser::MulOpContext::DIV() {
  return getToken(CACTParser::DIV, 0);
}

tree::TerminalNode* CACTParser::MulOpContext::MOD() {
  return getToken(CACTParser::MOD, 0);
}


size_t CACTParser::MulOpContext::getRuleIndex() const {
  return CACTParser::RuleMulOp;
}

void CACTParser::MulOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulOp(this);
}

void CACTParser::MulOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulOp(this);
}

CACTParser::MulOpContext* CACTParser::mulOp() {
  MulOpContext *_localctx = _tracker.createInstance<MulOpContext>(_ctx, getState());
  enterRule(_localctx, 48, CACTParser::RuleMulOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::MUL)
      | (1ULL << CACTParser::DIV)
      | (1ULL << CACTParser::MOD))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

CACTParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::MulExpContext* CACTParser::AddExpContext::mulExp() {
  return getRuleContext<CACTParser::MulExpContext>(0);
}

CACTParser::AddExpContext* CACTParser::AddExpContext::addExp() {
  return getRuleContext<CACTParser::AddExpContext>(0);
}

CACTParser::AddOpContext* CACTParser::AddExpContext::addOp() {
  return getRuleContext<CACTParser::AddOpContext>(0);
}


size_t CACTParser::AddExpContext::getRuleIndex() const {
  return CACTParser::RuleAddExp;
}

void CACTParser::AddExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExp(this);
}

void CACTParser::AddExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExp(this);
}


CACTParser::AddExpContext* CACTParser::addExp() {
   return addExp(0);
}

CACTParser::AddExpContext* CACTParser::addExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CACTParser::AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, parentState);
  CACTParser::AddExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CACTParser::RuleAddExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(285);
    mulExp(0);
    _ctx->stop = _input->LT(-1);
    setState(293);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddExp);
        setState(287);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(288);
        addOp();
        setState(289);
        mulExp(0); 
      }
      setState(295);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddOpContext ------------------------------------------------------------------

CACTParser::AddOpContext::AddOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::AddOpContext::ADD() {
  return getToken(CACTParser::ADD, 0);
}

tree::TerminalNode* CACTParser::AddOpContext::SUB() {
  return getToken(CACTParser::SUB, 0);
}


size_t CACTParser::AddOpContext::getRuleIndex() const {
  return CACTParser::RuleAddOp;
}

void CACTParser::AddOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddOp(this);
}

void CACTParser::AddOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddOp(this);
}

CACTParser::AddOpContext* CACTParser::addOp() {
  AddOpContext *_localctx = _tracker.createInstance<AddOpContext>(_ctx, getState());
  enterRule(_localctx, 52, CACTParser::RuleAddOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    _la = _input->LA(1);
    if (!(_la == CACTParser::ADD

    || _la == CACTParser::SUB)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

CACTParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::AddExpContext* CACTParser::RelExpContext::addExp() {
  return getRuleContext<CACTParser::AddExpContext>(0);
}

tree::TerminalNode* CACTParser::RelExpContext::BoolConst() {
  return getToken(CACTParser::BoolConst, 0);
}

CACTParser::RelExpContext* CACTParser::RelExpContext::relExp() {
  return getRuleContext<CACTParser::RelExpContext>(0);
}

CACTParser::RelOpContext* CACTParser::RelExpContext::relOp() {
  return getRuleContext<CACTParser::RelOpContext>(0);
}


size_t CACTParser::RelExpContext::getRuleIndex() const {
  return CACTParser::RuleRelExp;
}

void CACTParser::RelExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelExp(this);
}

void CACTParser::RelExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelExp(this);
}


CACTParser::RelExpContext* CACTParser::relExp() {
   return relExp(0);
}

CACTParser::RelExpContext* CACTParser::relExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CACTParser::RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, parentState);
  CACTParser::RelExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, CACTParser::RuleRelExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(301);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::LeftParen:
      case CACTParser::ADD:
      case CACTParser::SUB:
      case CACTParser::NOT:
      case CACTParser::Ident:
      case CACTParser::IntConst:
      case CACTParser::FloatConst:
      case CACTParser::DoubleConst: {
        setState(299);
        addExp(0);
        break;
      }

      case CACTParser::BoolConst: {
        setState(300);
        match(CACTParser::BoolConst);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(309);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelExp);
        setState(303);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(304);
        relOp();
        setState(305);
        addExp(0); 
      }
      setState(311);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelOpContext ------------------------------------------------------------------

CACTParser::RelOpContext::RelOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::RelOpContext::LEQ() {
  return getToken(CACTParser::LEQ, 0);
}

tree::TerminalNode* CACTParser::RelOpContext::GEQ() {
  return getToken(CACTParser::GEQ, 0);
}

tree::TerminalNode* CACTParser::RelOpContext::LT() {
  return getToken(CACTParser::LT, 0);
}

tree::TerminalNode* CACTParser::RelOpContext::GT() {
  return getToken(CACTParser::GT, 0);
}


size_t CACTParser::RelOpContext::getRuleIndex() const {
  return CACTParser::RuleRelOp;
}

void CACTParser::RelOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelOp(this);
}

void CACTParser::RelOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelOp(this);
}

CACTParser::RelOpContext* CACTParser::relOp() {
  RelOpContext *_localctx = _tracker.createInstance<RelOpContext>(_ctx, getState());
  enterRule(_localctx, 56, CACTParser::RuleRelOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::LEQ)
      | (1ULL << CACTParser::GEQ)
      | (1ULL << CACTParser::LT)
      | (1ULL << CACTParser::GT))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

CACTParser::EqExpContext::EqExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::RelExpContext* CACTParser::EqExpContext::relExp() {
  return getRuleContext<CACTParser::RelExpContext>(0);
}

CACTParser::EqExpContext* CACTParser::EqExpContext::eqExp() {
  return getRuleContext<CACTParser::EqExpContext>(0);
}

CACTParser::EqOpContext* CACTParser::EqExpContext::eqOp() {
  return getRuleContext<CACTParser::EqOpContext>(0);
}


size_t CACTParser::EqExpContext::getRuleIndex() const {
  return CACTParser::RuleEqExp;
}

void CACTParser::EqExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqExp(this);
}

void CACTParser::EqExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqExp(this);
}


CACTParser::EqExpContext* CACTParser::eqExp() {
   return eqExp(0);
}

CACTParser::EqExpContext* CACTParser::eqExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CACTParser::EqExpContext *_localctx = _tracker.createInstance<EqExpContext>(_ctx, parentState);
  CACTParser::EqExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, CACTParser::RuleEqExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(315);
    relExp(0);
    _ctx->stop = _input->LT(-1);
    setState(323);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EqExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleEqExp);
        setState(317);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(318);
        eqOp();
        setState(319);
        relExp(0); 
      }
      setState(325);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqOpContext ------------------------------------------------------------------

CACTParser::EqOpContext::EqOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::EqOpContext::EQ() {
  return getToken(CACTParser::EQ, 0);
}

tree::TerminalNode* CACTParser::EqOpContext::NEQ() {
  return getToken(CACTParser::NEQ, 0);
}


size_t CACTParser::EqOpContext::getRuleIndex() const {
  return CACTParser::RuleEqOp;
}

void CACTParser::EqOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqOp(this);
}

void CACTParser::EqOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqOp(this);
}

CACTParser::EqOpContext* CACTParser::eqOp() {
  EqOpContext *_localctx = _tracker.createInstance<EqOpContext>(_ctx, getState());
  enterRule(_localctx, 60, CACTParser::RuleEqOp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(326);
    _la = _input->LA(1);
    if (!(_la == CACTParser::EQ

    || _la == CACTParser::NEQ)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LAndExpContext ------------------------------------------------------------------

CACTParser::LAndExpContext::LAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::EqExpContext* CACTParser::LAndExpContext::eqExp() {
  return getRuleContext<CACTParser::EqExpContext>(0);
}

CACTParser::LAndExpContext* CACTParser::LAndExpContext::lAndExp() {
  return getRuleContext<CACTParser::LAndExpContext>(0);
}

tree::TerminalNode* CACTParser::LAndExpContext::AND() {
  return getToken(CACTParser::AND, 0);
}


size_t CACTParser::LAndExpContext::getRuleIndex() const {
  return CACTParser::RuleLAndExp;
}

void CACTParser::LAndExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLAndExp(this);
}

void CACTParser::LAndExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLAndExp(this);
}


CACTParser::LAndExpContext* CACTParser::lAndExp() {
   return lAndExp(0);
}

CACTParser::LAndExpContext* CACTParser::lAndExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CACTParser::LAndExpContext *_localctx = _tracker.createInstance<LAndExpContext>(_ctx, parentState);
  CACTParser::LAndExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 62;
  enterRecursionRule(_localctx, 62, CACTParser::RuleLAndExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(329);
    eqExp(0);
    _ctx->stop = _input->LT(-1);
    setState(336);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LAndExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLAndExp);
        setState(331);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(332);
        match(CACTParser::AND);
        setState(333);
        eqExp(0); 
      }
      setState(338);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

CACTParser::LOrExpContext::LOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::LAndExpContext* CACTParser::LOrExpContext::lAndExp() {
  return getRuleContext<CACTParser::LAndExpContext>(0);
}

CACTParser::LOrExpContext* CACTParser::LOrExpContext::lOrExp() {
  return getRuleContext<CACTParser::LOrExpContext>(0);
}

tree::TerminalNode* CACTParser::LOrExpContext::OR() {
  return getToken(CACTParser::OR, 0);
}


size_t CACTParser::LOrExpContext::getRuleIndex() const {
  return CACTParser::RuleLOrExp;
}

void CACTParser::LOrExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLOrExp(this);
}

void CACTParser::LOrExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CACTListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLOrExp(this);
}


CACTParser::LOrExpContext* CACTParser::lOrExp() {
   return lOrExp(0);
}

CACTParser::LOrExpContext* CACTParser::lOrExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CACTParser::LOrExpContext *_localctx = _tracker.createInstance<LOrExpContext>(_ctx, parentState);
  CACTParser::LOrExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 64;
  enterRecursionRule(_localctx, 64, CACTParser::RuleLOrExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(340);
    lAndExp(0);
    _ctx->stop = _input->LT(-1);
    setState(347);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LOrExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLOrExp);
        setState(342);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(343);
        match(CACTParser::OR);
        setState(344);
        lAndExp(0); 
      }
      setState(349);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool CACTParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 23: return mulExpSempred(dynamic_cast<MulExpContext *>(context), predicateIndex);
    case 25: return addExpSempred(dynamic_cast<AddExpContext *>(context), predicateIndex);
    case 27: return relExpSempred(dynamic_cast<RelExpContext *>(context), predicateIndex);
    case 29: return eqExpSempred(dynamic_cast<EqExpContext *>(context), predicateIndex);
    case 31: return lAndExpSempred(dynamic_cast<LAndExpContext *>(context), predicateIndex);
    case 32: return lOrExpSempred(dynamic_cast<LOrExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CACTParser::mulExpSempred(MulExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CACTParser::addExpSempred(AddExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CACTParser::relExpSempred(RelExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CACTParser::eqExpSempred(EqExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CACTParser::lAndExpSempred(LAndExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CACTParser::lOrExpSempred(LOrExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CACTParser::_decisionToDFA;
atn::PredictionContextCache CACTParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CACTParser::_atn;
std::vector<uint16_t> CACTParser::_serializedATN;

std::vector<std::string> CACTParser::_ruleNames = {
  "compUnit", "decl", "constDecl", "bType", "arrayDims", "constDef", "constInitVal", 
  "varDecl", "varDef", "funcDef", "funcType", "funcFParam", "block", "stmt", 
  "exp", "constExp", "cond", "lVal", "primaryExp", "number", "unaryExp", 
  "unaryOp", "funcRParams", "mulExp", "mulOp", "addExp", "addOp", "relExp", 
  "relOp", "eqExp", "eqOp", "lAndExp", "lOrExp"
};

std::vector<std::string> CACTParser::_literalNames = {
  "", "'('", "')'", "'['", "']'", "'{'", "'}'", "';'", "','", "'const'", 
  "'void'", "'int'", "'bool'", "'float'", "'double'", "'if'", "'else'", 
  "'while'", "'break'", "'continue'", "'return'", "'='", "'+'", "'-'", "'!'", 
  "'*'", "'/'", "'%'", "'<='", "'>='", "'<'", "'>'", "'=='", "'!='", "'&&'", 
  "'||'"
};

std::vector<std::string> CACTParser::_symbolicNames = {
  "", "LeftParen", "RightParen", "LeftBracket", "RightBracket", "LeftBrace", 
  "RightBrace", "SEMICOLON", "COMMA", "CONST", "VOID", "INT", "BOOL", "FLOAT", 
  "DOUBLE", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN", "ASSIGN", 
  "ADD", "SUB", "NOT", "MUL", "DIV", "MOD", "LEQ", "GEQ", "LT", "GT", "EQ", 
  "NEQ", "AND", "OR", "BoolConst", "Ident", "IntConst", "FloatConst", "DoubleConst", 
  "NewLine", "WhiteSpace", "LineComment", "BlockComment"
};

dfa::Vocabulary CACTParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CACTParser::_tokenNames;

CACTParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x2e, 0x161, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x47, 0xa, 0x2, 0xd, 0x2, 0xe, 
    0x2, 0x48, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x4f, 0xa, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x56, 
    0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x59, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x62, 0xa, 0x6, 
    0xc, 0x6, 0xe, 0x6, 0x65, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 
    0x8, 0x71, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x74, 0xb, 0x8, 0x5, 0x8, 0x76, 
    0xa, 0x8, 0x3, 0x8, 0x5, 0x8, 0x79, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x7, 0x9, 0x7f, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x82, 0xb, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 
    0xa, 0x8a, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 
    0x90, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x94, 0xa, 0xb, 0xc, 0xb, 
    0xe, 0xb, 0x97, 0xb, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xa2, 0xa, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0xa8, 0xa, 0xd, 0xc, 
    0xd, 0xe, 0xd, 0xab, 0xb, 0xd, 0x5, 0xd, 0xad, 0xa, 0xd, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x7, 0xe, 0xb2, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xb5, 0xb, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x5, 0xf, 0xbf, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 
    0xca, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xd6, 0xa, 0xf, 
    0x5, 0xf, 0xd8, 0xa, 0xf, 0x3, 0xf, 0x5, 0xf, 0xdb, 0xa, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x5, 0x10, 0xdf, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 
    0xe3, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xec, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 
    0xef, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0xf7, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 
    0x16, 0x102, 0xa, 0x16, 0x3, 0x16, 0x5, 0x16, 0x105, 0xa, 0x16, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x7, 0x18, 0x10c, 
    0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 0x10f, 0xb, 0x18, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x7, 0x19, 0x118, 
    0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0x11b, 0xb, 0x19, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x7, 0x1b, 0x126, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 0x129, 0xb, 
    0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 
    0x130, 0xa, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x7, 0x1d, 
    0x136, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x139, 0xb, 0x1d, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x3, 0x1f, 0x7, 0x1f, 0x144, 0xa, 0x1f, 0xc, 0x1f, 0xe, 0x1f, 
    0x147, 0xb, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x7, 0x21, 0x151, 0xa, 0x21, 0xc, 0x21, 
    0xe, 0x21, 0x154, 0xb, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x7, 0x22, 0x15c, 0xa, 0x22, 0xc, 0x22, 0xe, 0x22, 
    0x15f, 0xb, 0x22, 0x3, 0x22, 0x2, 0x8, 0x30, 0x34, 0x38, 0x3c, 0x40, 
    0x42, 0x23, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x2, 0xa, 
    0x3, 0x2, 0xd, 0x10, 0x3, 0x2, 0xc, 0x10, 0x3, 0x2, 0x28, 0x2a, 0x3, 
    0x2, 0x18, 0x1a, 0x3, 0x2, 0x1b, 0x1d, 0x3, 0x2, 0x18, 0x19, 0x3, 0x2, 
    0x1e, 0x21, 0x3, 0x2, 0x22, 0x23, 0x2, 0x16a, 0x2, 0x46, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x6, 0x50, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x5c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x63, 0x3, 0x2, 0x2, 0x2, 0xc, 0x66, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x78, 0x3, 0x2, 0x2, 0x2, 0x10, 0x7a, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x85, 0x3, 0x2, 0x2, 0x2, 0x14, 0x8b, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x18, 0x9d, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0xae, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xda, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0xde, 0x3, 0x2, 0x2, 0x2, 0x20, 0xe2, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0xe4, 0x3, 0x2, 0x2, 0x2, 0x24, 0xe6, 0x3, 0x2, 0x2, 0x2, 0x26, 0xf6, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0xf8, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x104, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x106, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x108, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x110, 0x3, 0x2, 0x2, 0x2, 0x32, 0x11c, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x36, 0x12a, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x13c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x148, 0x3, 0x2, 0x2, 0x2, 0x40, 0x14a, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x155, 0x3, 0x2, 0x2, 0x2, 0x44, 0x47, 0x5, 
    0x4, 0x3, 0x2, 0x45, 0x47, 0x5, 0x14, 0xb, 0x2, 0x46, 0x44, 0x3, 0x2, 
    0x2, 0x2, 0x46, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 
    0x49, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x2, 0x2, 0x3, 0x4b, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4f, 0x5, 0x6, 0x4, 0x2, 0x4d, 0x4f, 
    0x5, 0x10, 0x9, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4d, 0x3, 
    0x2, 0x2, 0x2, 0x4f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x7, 0xb, 
    0x2, 0x2, 0x51, 0x52, 0x5, 0x8, 0x5, 0x2, 0x52, 0x57, 0x5, 0xc, 0x7, 
    0x2, 0x53, 0x54, 0x7, 0xa, 0x2, 0x2, 0x54, 0x56, 0x5, 0xc, 0x7, 0x2, 
    0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x56, 0x59, 0x3, 0x2, 0x2, 0x2, 0x57, 
    0x55, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5a, 
    0x3, 0x2, 0x2, 0x2, 0x59, 0x57, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x7, 
    0x9, 0x2, 0x2, 0x5b, 0x7, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x9, 0x2, 
    0x2, 0x2, 0x5d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0x5, 0x2, 
    0x2, 0x5f, 0x60, 0x7, 0x28, 0x2, 0x2, 0x60, 0x62, 0x7, 0x6, 0x2, 0x2, 
    0x61, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x62, 0x65, 0x3, 0x2, 0x2, 0x2, 0x63, 
    0x61, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 
    0x27, 0x2, 0x2, 0x67, 0x68, 0x5, 0xa, 0x6, 0x2, 0x68, 0x69, 0x7, 0x17, 
    0x2, 0x2, 0x69, 0x6a, 0x5, 0xe, 0x8, 0x2, 0x6a, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x79, 0x5, 0x20, 0x11, 0x2, 0x6c, 0x75, 0x7, 0x7, 0x2, 0x2, 
    0x6d, 0x72, 0x5, 0xe, 0x8, 0x2, 0x6e, 0x6f, 0x7, 0xa, 0x2, 0x2, 0x6f, 
    0x71, 0x5, 0xe, 0x8, 0x2, 0x70, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x71, 0x74, 
    0x3, 0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 
    0x2, 0x2, 0x2, 0x73, 0x76, 0x3, 0x2, 0x2, 0x2, 0x74, 0x72, 0x3, 0x2, 
    0x2, 0x2, 0x75, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x3, 0x2, 0x2, 
    0x2, 0x76, 0x77, 0x3, 0x2, 0x2, 0x2, 0x77, 0x79, 0x7, 0x8, 0x2, 0x2, 
    0x78, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x78, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x79, 
    0xf, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x5, 0x8, 0x5, 0x2, 0x7b, 0x80, 
    0x5, 0x12, 0xa, 0x2, 0x7c, 0x7d, 0x7, 0xa, 0x2, 0x2, 0x7d, 0x7f, 0x5, 
    0x12, 0xa, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x82, 0x3, 0x2, 
    0x2, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 0x81, 0x3, 0x2, 0x2, 
    0x2, 0x81, 0x83, 0x3, 0x2, 0x2, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 
    0x83, 0x84, 0x7, 0x9, 0x2, 0x2, 0x84, 0x11, 0x3, 0x2, 0x2, 0x2, 0x85, 
    0x86, 0x7, 0x27, 0x2, 0x2, 0x86, 0x89, 0x5, 0xa, 0x6, 0x2, 0x87, 0x88, 
    0x7, 0x17, 0x2, 0x2, 0x88, 0x8a, 0x5, 0xe, 0x8, 0x2, 0x89, 0x87, 0x3, 
    0x2, 0x2, 0x2, 0x89, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x8b, 0x8c, 0x5, 0x16, 0xc, 0x2, 0x8c, 0x8d, 0x7, 0x27, 0x2, 
    0x2, 0x8d, 0x8f, 0x7, 0x3, 0x2, 0x2, 0x8e, 0x90, 0x5, 0x18, 0xd, 0x2, 
    0x8f, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 0x3, 0x2, 0x2, 0x2, 0x90, 
    0x95, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x7, 0xa, 0x2, 0x2, 0x92, 0x94, 
    0x5, 0x18, 0xd, 0x2, 0x93, 0x91, 0x3, 0x2, 0x2, 0x2, 0x94, 0x97, 0x3, 
    0x2, 0x2, 0x2, 0x95, 0x93, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x98, 0x3, 0x2, 0x2, 0x2, 0x97, 0x95, 0x3, 0x2, 0x2, 
    0x2, 0x98, 0x99, 0x7, 0x4, 0x2, 0x2, 0x99, 0x9a, 0x5, 0x1a, 0xe, 0x2, 
    0x9a, 0x15, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x9, 0x3, 0x2, 0x2, 0x9c, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 0x5, 0x8, 0x5, 0x2, 0x9e, 0xac, 
    0x7, 0x27, 0x2, 0x2, 0x9f, 0xa1, 0x7, 0x5, 0x2, 0x2, 0xa0, 0xa2, 0x7, 
    0x28, 0x2, 0x2, 0xa1, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 0x2, 
    0x2, 0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa9, 0x7, 0x6, 0x2, 
    0x2, 0xa4, 0xa5, 0x7, 0x5, 0x2, 0x2, 0xa5, 0xa6, 0x7, 0x28, 0x2, 0x2, 
    0xa6, 0xa8, 0x7, 0x6, 0x2, 0x2, 0xa7, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa8, 
    0xab, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 
    0x3, 0x2, 0x2, 0x2, 0xaa, 0xad, 0x3, 0x2, 0x2, 0x2, 0xab, 0xa9, 0x3, 
    0x2, 0x2, 0x2, 0xac, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x3, 0x2, 
    0x2, 0x2, 0xad, 0x19, 0x3, 0x2, 0x2, 0x2, 0xae, 0xb3, 0x7, 0x7, 0x2, 
    0x2, 0xaf, 0xb2, 0x5, 0x4, 0x3, 0x2, 0xb0, 0xb2, 0x5, 0x1c, 0xf, 0x2, 
    0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb2, 
    0xb5, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 
    0x3, 0x2, 0x2, 0x2, 0xb4, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb3, 0x3, 
    0x2, 0x2, 0x2, 0xb6, 0xb7, 0x7, 0x8, 0x2, 0x2, 0xb7, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0xb8, 0xb9, 0x5, 0x24, 0x13, 0x2, 0xb9, 0xba, 0x7, 0x17, 0x2, 
    0x2, 0xba, 0xbb, 0x5, 0x1e, 0x10, 0x2, 0xbb, 0xbc, 0x7, 0x9, 0x2, 0x2, 
    0xbc, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbf, 0x5, 0x1e, 0x10, 0x2, 0xbe, 
    0xbd, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 
    0x3, 0x2, 0x2, 0x2, 0xc0, 0xdb, 0x7, 0x9, 0x2, 0x2, 0xc1, 0xdb, 0x5, 
    0x1a, 0xe, 0x2, 0xc2, 0xc3, 0x7, 0x11, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x3, 
    0x2, 0x2, 0xc4, 0xc5, 0x5, 0x22, 0x12, 0x2, 0xc5, 0xc6, 0x7, 0x4, 0x2, 
    0x2, 0xc6, 0xc9, 0x5, 0x1c, 0xf, 0x2, 0xc7, 0xc8, 0x7, 0x12, 0x2, 0x2, 
    0xc8, 0xca, 0x5, 0x1c, 0xf, 0x2, 0xc9, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc9, 
    0xca, 0x3, 0x2, 0x2, 0x2, 0xca, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 
    0x7, 0x13, 0x2, 0x2, 0xcc, 0xcd, 0x7, 0x3, 0x2, 0x2, 0xcd, 0xce, 0x5, 
    0x22, 0x12, 0x2, 0xce, 0xcf, 0x7, 0x4, 0x2, 0x2, 0xcf, 0xd0, 0x5, 0x1c, 
    0xf, 0x2, 0xd0, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd8, 0x7, 0x14, 0x2, 
    0x2, 0xd2, 0xd8, 0x7, 0x15, 0x2, 0x2, 0xd3, 0xd5, 0x7, 0x16, 0x2, 0x2, 
    0xd4, 0xd6, 0x5, 0x1e, 0x10, 0x2, 0xd5, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd5, 
    0xd6, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd1, 
    0x3, 0x2, 0x2, 0x2, 0xd7, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd3, 0x3, 
    0x2, 0x2, 0x2, 0xd8, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xdb, 0x7, 0x9, 
    0x2, 0x2, 0xda, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xda, 0xbe, 0x3, 0x2, 0x2, 
    0x2, 0xda, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xda, 0xc2, 0x3, 0x2, 0x2, 0x2, 
    0xda, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xda, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xdb, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdf, 0x7, 0x26, 0x2, 0x2, 0xdd, 0xdf, 
    0x5, 0x34, 0x1b, 0x2, 0xde, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdd, 0x3, 
    0x2, 0x2, 0x2, 0xdf, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xe3, 0x5, 0x28, 
    0x15, 0x2, 0xe1, 0xe3, 0x7, 0x26, 0x2, 0x2, 0xe2, 0xe0, 0x3, 0x2, 0x2, 
    0x2, 0xe2, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe3, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0xe4, 0xe5, 0x5, 0x42, 0x22, 0x2, 0xe5, 0x23, 0x3, 0x2, 0x2, 0x2, 0xe6, 
    0xed, 0x7, 0x27, 0x2, 0x2, 0xe7, 0xe8, 0x7, 0x5, 0x2, 0x2, 0xe8, 0xe9, 
    0x5, 0x1e, 0x10, 0x2, 0xe9, 0xea, 0x7, 0x6, 0x2, 0x2, 0xea, 0xec, 0x3, 
    0x2, 0x2, 0x2, 0xeb, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xec, 0xef, 0x3, 0x2, 
    0x2, 0x2, 0xed, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x3, 0x2, 0x2, 
    0x2, 0xee, 0x25, 0x3, 0x2, 0x2, 0x2, 0xef, 0xed, 0x3, 0x2, 0x2, 0x2, 
    0xf0, 0xf7, 0x5, 0x28, 0x15, 0x2, 0xf1, 0xf7, 0x5, 0x24, 0x13, 0x2, 
    0xf2, 0xf3, 0x7, 0x3, 0x2, 0x2, 0xf3, 0xf4, 0x5, 0x1e, 0x10, 0x2, 0xf4, 
    0xf5, 0x7, 0x4, 0x2, 0x2, 0xf5, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf0, 
    0x3, 0x2, 0x2, 0x2, 0xf6, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf2, 0x3, 
    0x2, 0x2, 0x2, 0xf7, 0x27, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf9, 0x9, 0x4, 
    0x2, 0x2, 0xf9, 0x29, 0x3, 0x2, 0x2, 0x2, 0xfa, 0x105, 0x5, 0x26, 0x14, 
    0x2, 0xfb, 0xfc, 0x5, 0x2c, 0x17, 0x2, 0xfc, 0xfd, 0x5, 0x2a, 0x16, 
    0x2, 0xfd, 0x105, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xff, 0x7, 0x27, 0x2, 0x2, 
    0xff, 0x101, 0x7, 0x3, 0x2, 0x2, 0x100, 0x102, 0x5, 0x2e, 0x18, 0x2, 
    0x101, 0x100, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x3, 0x2, 0x2, 0x2, 
    0x102, 0x103, 0x3, 0x2, 0x2, 0x2, 0x103, 0x105, 0x7, 0x4, 0x2, 0x2, 
    0x104, 0xfa, 0x3, 0x2, 0x2, 0x2, 0x104, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x104, 
    0xfe, 0x3, 0x2, 0x2, 0x2, 0x105, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x106, 0x107, 
    0x9, 0x5, 0x2, 0x2, 0x107, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x108, 0x10d, 0x5, 
    0x1e, 0x10, 0x2, 0x109, 0x10a, 0x7, 0xa, 0x2, 0x2, 0x10a, 0x10c, 0x5, 
    0x1e, 0x10, 0x2, 0x10b, 0x109, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10f, 0x3, 
    0x2, 0x2, 0x2, 0x10d, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x3, 
    0x2, 0x2, 0x2, 0x10e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x10d, 0x3, 0x2, 
    0x2, 0x2, 0x110, 0x111, 0x8, 0x19, 0x1, 0x2, 0x111, 0x112, 0x5, 0x2a, 
    0x16, 0x2, 0x112, 0x119, 0x3, 0x2, 0x2, 0x2, 0x113, 0x114, 0xc, 0x3, 
    0x2, 0x2, 0x114, 0x115, 0x5, 0x32, 0x1a, 0x2, 0x115, 0x116, 0x5, 0x2a, 
    0x16, 0x2, 0x116, 0x118, 0x3, 0x2, 0x2, 0x2, 0x117, 0x113, 0x3, 0x2, 
    0x2, 0x2, 0x118, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x119, 0x117, 0x3, 0x2, 
    0x2, 0x2, 0x119, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x31, 0x3, 0x2, 0x2, 
    0x2, 0x11b, 0x119, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11d, 0x9, 0x6, 0x2, 
    0x2, 0x11d, 0x33, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 0x8, 0x1b, 0x1, 
    0x2, 0x11f, 0x120, 0x5, 0x30, 0x19, 0x2, 0x120, 0x127, 0x3, 0x2, 0x2, 
    0x2, 0x121, 0x122, 0xc, 0x3, 0x2, 0x2, 0x122, 0x123, 0x5, 0x36, 0x1c, 
    0x2, 0x123, 0x124, 0x5, 0x30, 0x19, 0x2, 0x124, 0x126, 0x3, 0x2, 0x2, 
    0x2, 0x125, 0x121, 0x3, 0x2, 0x2, 0x2, 0x126, 0x129, 0x3, 0x2, 0x2, 
    0x2, 0x127, 0x125, 0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x3, 0x2, 0x2, 
    0x2, 0x128, 0x35, 0x3, 0x2, 0x2, 0x2, 0x129, 0x127, 0x3, 0x2, 0x2, 0x2, 
    0x12a, 0x12b, 0x9, 0x7, 0x2, 0x2, 0x12b, 0x37, 0x3, 0x2, 0x2, 0x2, 0x12c, 
    0x12d, 0x8, 0x1d, 0x1, 0x2, 0x12d, 0x130, 0x5, 0x34, 0x1b, 0x2, 0x12e, 
    0x130, 0x7, 0x26, 0x2, 0x2, 0x12f, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12f, 
    0x12e, 0x3, 0x2, 0x2, 0x2, 0x130, 0x137, 0x3, 0x2, 0x2, 0x2, 0x131, 
    0x132, 0xc, 0x4, 0x2, 0x2, 0x132, 0x133, 0x5, 0x3a, 0x1e, 0x2, 0x133, 
    0x134, 0x5, 0x34, 0x1b, 0x2, 0x134, 0x136, 0x3, 0x2, 0x2, 0x2, 0x135, 
    0x131, 0x3, 0x2, 0x2, 0x2, 0x136, 0x139, 0x3, 0x2, 0x2, 0x2, 0x137, 
    0x135, 0x3, 0x2, 0x2, 0x2, 0x137, 0x138, 0x3, 0x2, 0x2, 0x2, 0x138, 
    0x39, 0x3, 0x2, 0x2, 0x2, 0x139, 0x137, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x13b, 
    0x9, 0x8, 0x2, 0x2, 0x13b, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13d, 0x8, 
    0x1f, 0x1, 0x2, 0x13d, 0x13e, 0x5, 0x38, 0x1d, 0x2, 0x13e, 0x145, 0x3, 
    0x2, 0x2, 0x2, 0x13f, 0x140, 0xc, 0x3, 0x2, 0x2, 0x140, 0x141, 0x5, 
    0x3e, 0x20, 0x2, 0x141, 0x142, 0x5, 0x38, 0x1d, 0x2, 0x142, 0x144, 0x3, 
    0x2, 0x2, 0x2, 0x143, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x144, 0x147, 0x3, 
    0x2, 0x2, 0x2, 0x145, 0x143, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 0x3, 
    0x2, 0x2, 0x2, 0x146, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x147, 0x145, 0x3, 0x2, 
    0x2, 0x2, 0x148, 0x149, 0x9, 0x9, 0x2, 0x2, 0x149, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x14a, 0x14b, 0x8, 0x21, 0x1, 0x2, 0x14b, 0x14c, 0x5, 0x3c, 0x1f, 
    0x2, 0x14c, 0x152, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14e, 0xc, 0x3, 0x2, 
    0x2, 0x14e, 0x14f, 0x7, 0x24, 0x2, 0x2, 0x14f, 0x151, 0x5, 0x3c, 0x1f, 
    0x2, 0x150, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x151, 0x154, 0x3, 0x2, 0x2, 
    0x2, 0x152, 0x150, 0x3, 0x2, 0x2, 0x2, 0x152, 0x153, 0x3, 0x2, 0x2, 
    0x2, 0x153, 0x41, 0x3, 0x2, 0x2, 0x2, 0x154, 0x152, 0x3, 0x2, 0x2, 0x2, 
    0x155, 0x156, 0x8, 0x22, 0x1, 0x2, 0x156, 0x157, 0x5, 0x40, 0x21, 0x2, 
    0x157, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 0xc, 0x3, 0x2, 0x2, 
    0x159, 0x15a, 0x7, 0x25, 0x2, 0x2, 0x15a, 0x15c, 0x5, 0x40, 0x21, 0x2, 
    0x15b, 0x158, 0x3, 0x2, 0x2, 0x2, 0x15c, 0x15f, 0x3, 0x2, 0x2, 0x2, 
    0x15d, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x15e, 0x3, 0x2, 0x2, 0x2, 
    0x15e, 0x43, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x26, 
    0x46, 0x48, 0x4e, 0x57, 0x63, 0x72, 0x75, 0x78, 0x80, 0x89, 0x8f, 0x95, 
    0xa1, 0xa9, 0xac, 0xb1, 0xb3, 0xbe, 0xc9, 0xd5, 0xd7, 0xda, 0xde, 0xe2, 
    0xed, 0xf6, 0x101, 0x104, 0x10d, 0x119, 0x127, 0x12f, 0x137, 0x145, 
    0x152, 0x15d, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CACTParser::Initializer CACTParser::_init;
