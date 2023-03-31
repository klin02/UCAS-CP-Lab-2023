
    #include <vector>
    #include <string>


// Generated from CACT.g4 by ANTLR 4.8


#include "CACTVisitor.h"

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


antlrcpp::Any CACTParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
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
    setState(60); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(60);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(58);
        decl();
        break;
      }

      case 2: {
        setState(59);
        funcDef();
        break;
      }

      }
      setState(62); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::CONST)
      | (1ULL << CACTParser::VOID)
      | (1ULL << CACTParser::INT)
      | (1ULL << CACTParser::BOOL)
      | (1ULL << CACTParser::FLOAT)
      | (1ULL << CACTParser::DOUBLE))) != 0));
    setState(64);
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


antlrcpp::Any CACTParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::DeclContext* CACTParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, CACTParser::RuleDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(68);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(66);
        constDecl();
        break;
      }

      case CACTParser::INT:
      case CACTParser::BOOL:
      case CACTParser::FLOAT:
      case CACTParser::DOUBLE: {
        enterOuterAlt(_localctx, 2);
        setState(67);
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


antlrcpp::Any CACTParser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
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
    setState(70);
    match(CACTParser::CONST);
    setState(71);
    bType();
    setState(72);
    constDef();
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(73);
      match(CACTParser::COMMA);
      setState(74);
      constDef();
      setState(79);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(80);
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


antlrcpp::Any CACTParser::BTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitBType(this);
  else
    return visitor->visitChildren(this);
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
    setState(82);
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

//----------------- ConstDefContext ------------------------------------------------------------------

CACTParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CACTParser::ConstDefContext::Ident() {
  return getToken(CACTParser::Ident, 0);
}

tree::TerminalNode* CACTParser::ConstDefContext::ASSIGN() {
  return getToken(CACTParser::ASSIGN, 0);
}

CACTParser::ConstInitValContext* CACTParser::ConstDefContext::constInitVal() {
  return getRuleContext<CACTParser::ConstInitValContext>(0);
}

std::vector<tree::TerminalNode *> CACTParser::ConstDefContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::ConstDefContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::ConstDefContext::IntConst() {
  return getTokens(CACTParser::IntConst);
}

tree::TerminalNode* CACTParser::ConstDefContext::IntConst(size_t i) {
  return getToken(CACTParser::IntConst, i);
}

std::vector<tree::TerminalNode *> CACTParser::ConstDefContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::ConstDefContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
}


size_t CACTParser::ConstDefContext::getRuleIndex() const {
  return CACTParser::RuleConstDef;
}


antlrcpp::Any CACTParser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConstDefContext* CACTParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 8, CACTParser::RuleConstDef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(CACTParser::Ident);
    setState(90);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(85);
      match(CACTParser::LeftBracket);
      setState(86);
      match(CACTParser::IntConst);
      setState(87);
      match(CACTParser::RightBracket);
      setState(92);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(93);
    match(CACTParser::ASSIGN);
    setState(94);
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


antlrcpp::Any CACTParser::ConstInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstInitVal(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConstInitValContext* CACTParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 10, CACTParser::RuleConstInitVal);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(109);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::BoolConst:
      case CACTParser::IntConst:
      case CACTParser::FloatConst:
      case CACTParser::DoubleConst: {
        enterOuterAlt(_localctx, 1);
        setState(96);
        constExp();
        break;
      }

      case CACTParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(97);
        match(CACTParser::LeftBrace);
        setState(106);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << CACTParser::LeftBrace)
          | (1ULL << CACTParser::BoolConst)
          | (1ULL << CACTParser::IntConst)
          | (1ULL << CACTParser::FloatConst)
          | (1ULL << CACTParser::DoubleConst))) != 0)) {
          setState(98);
          constInitVal();
          setState(103);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == CACTParser::COMMA) {
            setState(99);
            match(CACTParser::COMMA);
            setState(100);
            constInitVal();
            setState(105);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(108);
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


antlrcpp::Any CACTParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::VarDeclContext* CACTParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 12, CACTParser::RuleVarDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    bType();
    setState(112);
    varDef();
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(113);
      match(CACTParser::COMMA);
      setState(114);
      varDef();
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(120);
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

std::vector<tree::TerminalNode *> CACTParser::VarDefContext::LeftBracket() {
  return getTokens(CACTParser::LeftBracket);
}

tree::TerminalNode* CACTParser::VarDefContext::LeftBracket(size_t i) {
  return getToken(CACTParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> CACTParser::VarDefContext::IntConst() {
  return getTokens(CACTParser::IntConst);
}

tree::TerminalNode* CACTParser::VarDefContext::IntConst(size_t i) {
  return getToken(CACTParser::IntConst, i);
}

std::vector<tree::TerminalNode *> CACTParser::VarDefContext::RightBracket() {
  return getTokens(CACTParser::RightBracket);
}

tree::TerminalNode* CACTParser::VarDefContext::RightBracket(size_t i) {
  return getToken(CACTParser::RightBracket, i);
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


antlrcpp::Any CACTParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::VarDefContext* CACTParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 14, CACTParser::RuleVarDef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(CACTParser::Ident);
    setState(128);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::LeftBracket) {
      setState(123);
      match(CACTParser::LeftBracket);
      setState(124);
      match(CACTParser::IntConst);
      setState(125);
      match(CACTParser::RightBracket);
      setState(130);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(133);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::ASSIGN) {
      setState(131);
      match(CACTParser::ASSIGN);
      setState(132);
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

CACTParser::FuncFParamsContext* CACTParser::FuncDefContext::funcFParams() {
  return getRuleContext<CACTParser::FuncFParamsContext>(0);
}


size_t CACTParser::FuncDefContext::getRuleIndex() const {
  return CACTParser::RuleFuncDef;
}


antlrcpp::Any CACTParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FuncDefContext* CACTParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 16, CACTParser::RuleFuncDef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
    funcType();
    setState(136);
    match(CACTParser::Ident);
    setState(137);
    match(CACTParser::LeftParen);
    setState(139);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CACTParser::INT)
      | (1ULL << CACTParser::BOOL)
      | (1ULL << CACTParser::FLOAT)
      | (1ULL << CACTParser::DOUBLE))) != 0)) {
      setState(138);
      funcFParams();
    }
    setState(141);
    match(CACTParser::RightParen);
    setState(142);
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


antlrcpp::Any CACTParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FuncTypeContext* CACTParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 18, CACTParser::RuleFuncType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
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

//----------------- FuncFParamsContext ------------------------------------------------------------------

CACTParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CACTParser::FuncFParamContext *> CACTParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<CACTParser::FuncFParamContext>();
}

CACTParser::FuncFParamContext* CACTParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<CACTParser::FuncFParamContext>(i);
}

std::vector<tree::TerminalNode *> CACTParser::FuncFParamsContext::COMMA() {
  return getTokens(CACTParser::COMMA);
}

tree::TerminalNode* CACTParser::FuncFParamsContext::COMMA(size_t i) {
  return getToken(CACTParser::COMMA, i);
}


size_t CACTParser::FuncFParamsContext::getRuleIndex() const {
  return CACTParser::RuleFuncFParams;
}


antlrcpp::Any CACTParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::FuncFParamsContext* CACTParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 20, CACTParser::RuleFuncFParams);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    funcFParam();
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(147);
      match(CACTParser::COMMA);
      setState(148);
      funcFParam();
      setState(153);
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


antlrcpp::Any CACTParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
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
    setState(154);
    bType();
    setState(155);
    match(CACTParser::Ident);
    setState(169);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CACTParser::LeftBracket) {
      setState(156);
      match(CACTParser::LeftBracket);
      setState(158);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CACTParser::IntConst) {
        setState(157);
        match(CACTParser::IntConst);
      }
      setState(160);
      match(CACTParser::RightBracket);
      setState(166);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CACTParser::LeftBracket) {
        setState(161);
        match(CACTParser::LeftBracket);
        setState(162);
        match(CACTParser::IntConst);
        setState(163);
        match(CACTParser::RightBracket);
        setState(168);
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

std::vector<CACTParser::BlockItemContext *> CACTParser::BlockContext::blockItem() {
  return getRuleContexts<CACTParser::BlockItemContext>();
}

CACTParser::BlockItemContext* CACTParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<CACTParser::BlockItemContext>(i);
}


size_t CACTParser::BlockContext::getRuleIndex() const {
  return CACTParser::RuleBlock;
}


antlrcpp::Any CACTParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
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
    setState(171);
    match(CACTParser::LeftBrace);
    setState(175);
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
      setState(172);
      blockItem();
      setState(177);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(178);
    match(CACTParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

CACTParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::DeclContext* CACTParser::BlockItemContext::decl() {
  return getRuleContext<CACTParser::DeclContext>(0);
}

CACTParser::StmtContext* CACTParser::BlockItemContext::stmt() {
  return getRuleContext<CACTParser::StmtContext>(0);
}


size_t CACTParser::BlockItemContext::getRuleIndex() const {
  return CACTParser::RuleBlockItem;
}


antlrcpp::Any CACTParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::BlockItemContext* CACTParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 26, CACTParser::RuleBlockItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(182);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CACTParser::CONST:
      case CACTParser::INT:
      case CACTParser::BOOL:
      case CACTParser::FLOAT:
      case CACTParser::DOUBLE: {
        enterOuterAlt(_localctx, 1);
        setState(180);
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
        enterOuterAlt(_localctx, 2);
        setState(181);
        stmt();
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

//----------------- StmtContext ------------------------------------------------------------------

CACTParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CACTParser::LValContext* CACTParser::StmtContext::lVal() {
  return getRuleContext<CACTParser::LValContext>(0);
}

tree::TerminalNode* CACTParser::StmtContext::ASSIGN() {
  return getToken(CACTParser::ASSIGN, 0);
}

CACTParser::ExpContext* CACTParser::StmtContext::exp() {
  return getRuleContext<CACTParser::ExpContext>(0);
}

tree::TerminalNode* CACTParser::StmtContext::SEMICOLON() {
  return getToken(CACTParser::SEMICOLON, 0);
}

CACTParser::BlockContext* CACTParser::StmtContext::block() {
  return getRuleContext<CACTParser::BlockContext>(0);
}

tree::TerminalNode* CACTParser::StmtContext::IF() {
  return getToken(CACTParser::IF, 0);
}

tree::TerminalNode* CACTParser::StmtContext::LeftParen() {
  return getToken(CACTParser::LeftParen, 0);
}

CACTParser::CondContext* CACTParser::StmtContext::cond() {
  return getRuleContext<CACTParser::CondContext>(0);
}

tree::TerminalNode* CACTParser::StmtContext::RightParen() {
  return getToken(CACTParser::RightParen, 0);
}

std::vector<CACTParser::StmtContext *> CACTParser::StmtContext::stmt() {
  return getRuleContexts<CACTParser::StmtContext>();
}

CACTParser::StmtContext* CACTParser::StmtContext::stmt(size_t i) {
  return getRuleContext<CACTParser::StmtContext>(i);
}

tree::TerminalNode* CACTParser::StmtContext::ELSE() {
  return getToken(CACTParser::ELSE, 0);
}

tree::TerminalNode* CACTParser::StmtContext::WHILE() {
  return getToken(CACTParser::WHILE, 0);
}

tree::TerminalNode* CACTParser::StmtContext::BREAK() {
  return getToken(CACTParser::BREAK, 0);
}

tree::TerminalNode* CACTParser::StmtContext::CONTINUE() {
  return getToken(CACTParser::CONTINUE, 0);
}

tree::TerminalNode* CACTParser::StmtContext::RETURN() {
  return getToken(CACTParser::RETURN, 0);
}


size_t CACTParser::StmtContext::getRuleIndex() const {
  return CACTParser::RuleStmt;
}


antlrcpp::Any CACTParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::StmtContext* CACTParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 28, CACTParser::RuleStmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(216);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(184);
      lVal();
      setState(185);
      match(CACTParser::ASSIGN);
      setState(186);
      exp();
      setState(187);
      match(CACTParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(190);
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
        setState(189);
        exp();
      }
      setState(192);
      match(CACTParser::SEMICOLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(193);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(194);
      match(CACTParser::IF);
      setState(195);
      match(CACTParser::LeftParen);
      setState(196);
      cond();
      setState(197);
      match(CACTParser::RightParen);
      setState(198);
      stmt();
      setState(201);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
      case 1: {
        setState(199);
        match(CACTParser::ELSE);
        setState(200);
        stmt();
        break;
      }

      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(203);
      match(CACTParser::WHILE);
      setState(204);
      match(CACTParser::LeftParen);
      setState(205);
      cond();
      setState(206);
      match(CACTParser::RightParen);
      setState(207);
      stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(213);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CACTParser::BREAK: {
          setState(209);
          match(CACTParser::BREAK);
          break;
        }

        case CACTParser::CONTINUE: {
          setState(210);
          match(CACTParser::CONTINUE);
          break;
        }

        case CACTParser::RETURN: {
          setState(211);
          match(CACTParser::RETURN);
          setState(212);
          exp();
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


antlrcpp::Any CACTParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ExpContext* CACTParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 30, CACTParser::RuleExp);

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


antlrcpp::Any CACTParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::ConstExpContext* CACTParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 32, CACTParser::RuleConstExp);

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


antlrcpp::Any CACTParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::CondContext* CACTParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 34, CACTParser::RuleCond);

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


antlrcpp::Any CACTParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::LValContext* CACTParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 36, CACTParser::RuleLVal);

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


antlrcpp::Any CACTParser::PrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::PrimaryExpContext* CACTParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 38, CACTParser::RulePrimaryExp);

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


antlrcpp::Any CACTParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::NumberContext* CACTParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 40, CACTParser::RuleNumber);
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

CACTParser::UnaryExpContext* CACTParser::UnaryExpContext::unaryExp() {
  return getRuleContext<CACTParser::UnaryExpContext>(0);
}

tree::TerminalNode* CACTParser::UnaryExpContext::ADD() {
  return getToken(CACTParser::ADD, 0);
}

tree::TerminalNode* CACTParser::UnaryExpContext::SUB() {
  return getToken(CACTParser::SUB, 0);
}

tree::TerminalNode* CACTParser::UnaryExpContext::NOT() {
  return getToken(CACTParser::NOT, 0);
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


antlrcpp::Any CACTParser::UnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitUnaryExp(this);
  else
    return visitor->visitChildren(this);
}

CACTParser::UnaryExpContext* CACTParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 42, CACTParser::RuleUnaryExp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(257);
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
      setState(250);
      unaryExp();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(251);
      match(CACTParser::Ident);
      setState(252);
      match(CACTParser::LeftParen);
      setState(254);
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
        setState(253);
        funcRParams();
      }
      setState(256);
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


antlrcpp::Any CACTParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
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
    setState(259);
    exp();
    setState(264);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CACTParser::COMMA) {
      setState(260);
      match(CACTParser::COMMA);
      setState(261);
      exp();
      setState(266);
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

tree::TerminalNode* CACTParser::MulExpContext::MUL() {
  return getToken(CACTParser::MUL, 0);
}

tree::TerminalNode* CACTParser::MulExpContext::DIV() {
  return getToken(CACTParser::DIV, 0);
}

tree::TerminalNode* CACTParser::MulExpContext::MOD() {
  return getToken(CACTParser::MOD, 0);
}


size_t CACTParser::MulExpContext::getRuleIndex() const {
  return CACTParser::RuleMulExp;
}


antlrcpp::Any CACTParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
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

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(268);
    unaryExp();
    _ctx->stop = _input->LT(-1);
    setState(275);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulExp);
        setState(270);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(271);
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
        setState(272);
        unaryExp(); 
      }
      setState(277);
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

tree::TerminalNode* CACTParser::AddExpContext::ADD() {
  return getToken(CACTParser::ADD, 0);
}

tree::TerminalNode* CACTParser::AddExpContext::SUB() {
  return getToken(CACTParser::SUB, 0);
}


size_t CACTParser::AddExpContext::getRuleIndex() const {
  return CACTParser::RuleAddExp;
}


antlrcpp::Any CACTParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
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
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, CACTParser::RuleAddExp, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(279);
    mulExp(0);
    _ctx->stop = _input->LT(-1);
    setState(286);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddExp);
        setState(281);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(282);
        _la = _input->LA(1);
        if (!(_la == CACTParser::ADD

        || _la == CACTParser::SUB)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(283);
        mulExp(0); 
      }
      setState(288);
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

tree::TerminalNode* CACTParser::RelExpContext::LEQ() {
  return getToken(CACTParser::LEQ, 0);
}

tree::TerminalNode* CACTParser::RelExpContext::GEQ() {
  return getToken(CACTParser::GEQ, 0);
}

tree::TerminalNode* CACTParser::RelExpContext::LT() {
  return getToken(CACTParser::LT, 0);
}

tree::TerminalNode* CACTParser::RelExpContext::GT() {
  return getToken(CACTParser::GT, 0);
}


size_t CACTParser::RelExpContext::getRuleIndex() const {
  return CACTParser::RuleRelExp;
}


antlrcpp::Any CACTParser::RelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitRelExp(this);
  else
    return visitor->visitChildren(this);
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
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, CACTParser::RuleRelExp, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(292);
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
        setState(290);
        addExp(0);
        break;
      }

      case CACTParser::BoolConst: {
        setState(291);
        match(CACTParser::BoolConst);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(299);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelExp);
        setState(294);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(295);
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
        setState(296);
        addExp(0); 
      }
      setState(301);
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

tree::TerminalNode* CACTParser::EqExpContext::EQ() {
  return getToken(CACTParser::EQ, 0);
}

tree::TerminalNode* CACTParser::EqExpContext::NEQ() {
  return getToken(CACTParser::NEQ, 0);
}


size_t CACTParser::EqExpContext::getRuleIndex() const {
  return CACTParser::RuleEqExp;
}


antlrcpp::Any CACTParser::EqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitEqExp(this);
  else
    return visitor->visitChildren(this);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, CACTParser::RuleEqExp, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(303);
    relExp(0);
    _ctx->stop = _input->LT(-1);
    setState(310);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EqExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleEqExp);
        setState(305);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(306);
        _la = _input->LA(1);
        if (!(_la == CACTParser::EQ

        || _la == CACTParser::NEQ)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(307);
        relExp(0); 
      }
      setState(312);
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


antlrcpp::Any CACTParser::LAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLAndExp(this);
  else
    return visitor->visitChildren(this);
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
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, CACTParser::RuleLAndExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(314);
    eqExp(0);
    _ctx->stop = _input->LT(-1);
    setState(321);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LAndExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLAndExp);
        setState(316);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(317);
        match(CACTParser::AND);
        setState(318);
        eqExp(0); 
      }
      setState(323);
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


antlrcpp::Any CACTParser::LOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CACTVisitor*>(visitor))
    return parserVisitor->visitLOrExp(this);
  else
    return visitor->visitChildren(this);
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
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, CACTParser::RuleLOrExp, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(325);
    lAndExp(0);
    _ctx->stop = _input->LT(-1);
    setState(332);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LOrExpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLOrExp);
        setState(327);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(328);
        match(CACTParser::OR);
        setState(329);
        lAndExp(0); 
      }
      setState(334);
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
    case 24: return addExpSempred(dynamic_cast<AddExpContext *>(context), predicateIndex);
    case 25: return relExpSempred(dynamic_cast<RelExpContext *>(context), predicateIndex);
    case 26: return eqExpSempred(dynamic_cast<EqExpContext *>(context), predicateIndex);
    case 27: return lAndExpSempred(dynamic_cast<LAndExpContext *>(context), predicateIndex);
    case 28: return lOrExpSempred(dynamic_cast<LOrExpContext *>(context), predicateIndex);

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
  "compUnit", "decl", "constDecl", "bType", "constDef", "constInitVal", 
  "varDecl", "varDef", "funcDef", "funcType", "funcFParams", "funcFParam", 
  "block", "blockItem", "stmt", "exp", "constExp", "cond", "lVal", "primaryExp", 
  "number", "unaryExp", "funcRParams", "mulExp", "addExp", "relExp", "eqExp", 
  "lAndExp", "lOrExp"
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
    0x3, 0x2e, 0x152, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x3, 
    0x2, 0x3, 0x2, 0x6, 0x2, 0x3f, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x40, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x47, 0xa, 0x3, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x4e, 0xa, 0x4, 0xc, 
    0x4, 0xe, 0x4, 0x51, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x5b, 0xa, 0x6, 0xc, 
    0x6, 0xe, 0x6, 0x5e, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x68, 0xa, 0x7, 0xc, 
    0x7, 0xe, 0x7, 0x6b, 0xb, 0x7, 0x5, 0x7, 0x6d, 0xa, 0x7, 0x3, 0x7, 0x5, 
    0x7, 0x70, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 
    0x76, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x79, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x81, 0xa, 0x9, 0xc, 
    0x9, 0xe, 0x9, 0x84, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x88, 0xa, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x8e, 0xa, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x7, 0xc, 0x98, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x9b, 0xb, 0xc, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xa1, 0xa, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0xa7, 0xa, 0xd, 0xc, 0xd, 
    0xe, 0xd, 0xaa, 0xb, 0xd, 0x5, 0xd, 0xac, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 
    0x7, 0xe, 0xb0, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xb3, 0xb, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xb9, 0xa, 0xf, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xc1, 0xa, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xcc, 0xa, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xd8, 0xa, 0x10, 0x3, 0x10, 0x5, 
    0x10, 0xdb, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xdf, 0xa, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xe3, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0xec, 
    0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0xef, 0xb, 0x14, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0xf7, 0xa, 0x15, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x5, 0x17, 0x101, 0xa, 0x17, 0x3, 0x17, 0x5, 0x17, 
    0x104, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x7, 0x18, 0x109, 
    0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 0x10c, 0xb, 0x18, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x7, 0x19, 0x114, 0xa, 0x19, 
    0xc, 0x19, 0xe, 0x19, 0x117, 0xb, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x7, 0x1a, 0x11f, 0xa, 0x1a, 0xc, 0x1a, 
    0xe, 0x1a, 0x122, 0xb, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 
    0x127, 0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x7, 0x1b, 0x12c, 
    0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 0x12f, 0xb, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x137, 0xa, 0x1c, 
    0xc, 0x1c, 0xe, 0x1c, 0x13a, 0xb, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x7, 0x1d, 0x142, 0xa, 0x1d, 0xc, 0x1d, 
    0xe, 0x1d, 0x145, 0xb, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x14d, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 
    0x150, 0xb, 0x1e, 0x3, 0x1e, 0x2, 0x8, 0x30, 0x32, 0x34, 0x36, 0x38, 
    0x3a, 0x1f, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x2, 0xa, 0x3, 0x2, 0xd, 0x10, 0x3, 
    0x2, 0xc, 0x10, 0x3, 0x2, 0x28, 0x2a, 0x3, 0x2, 0x18, 0x1a, 0x3, 0x2, 
    0x1b, 0x1d, 0x3, 0x2, 0x18, 0x19, 0x3, 0x2, 0x1e, 0x21, 0x3, 0x2, 0x22, 
    0x23, 0x2, 0x15f, 0x2, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x4, 0x46, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x48, 0x3, 0x2, 0x2, 0x2, 0x8, 0x54, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x56, 0x3, 0x2, 0x2, 0x2, 0xc, 0x6f, 0x3, 0x2, 0x2, 0x2, 0xe, 0x71, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x12, 0x89, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x92, 0x3, 0x2, 0x2, 0x2, 0x16, 0x94, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x9c, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xad, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xda, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0xde, 0x3, 0x2, 0x2, 0x2, 0x22, 0xe2, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0xe4, 0x3, 0x2, 0x2, 0x2, 0x26, 0xe6, 0x3, 0x2, 0x2, 0x2, 0x28, 0xf6, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0xf8, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x103, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x105, 0x3, 0x2, 0x2, 0x2, 0x30, 0x10d, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0x118, 0x3, 0x2, 0x2, 0x2, 0x34, 0x126, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x130, 0x3, 0x2, 0x2, 0x2, 0x38, 0x13b, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0x146, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3f, 0x5, 0x4, 0x3, 0x2, 0x3d, 
    0x3f, 0x5, 0x12, 0xa, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3d, 
    0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 0x3e, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x43, 0x7, 0x2, 0x2, 0x3, 0x43, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x44, 0x47, 0x5, 0x6, 0x4, 0x2, 0x45, 0x47, 0x5, 0xe, 0x8, 0x2, 
    0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 0x46, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x7, 0xb, 0x2, 0x2, 0x49, 0x4a, 
    0x5, 0x8, 0x5, 0x2, 0x4a, 0x4f, 0x5, 0xa, 0x6, 0x2, 0x4b, 0x4c, 0x7, 
    0xa, 0x2, 0x2, 0x4c, 0x4e, 0x5, 0xa, 0x6, 0x2, 0x4d, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x51, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 
    0x2, 0x4f, 0x50, 0x3, 0x2, 0x2, 0x2, 0x50, 0x52, 0x3, 0x2, 0x2, 0x2, 
    0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0x9, 0x2, 0x2, 0x53, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x9, 0x2, 0x2, 0x2, 0x55, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x56, 0x5c, 0x7, 0x27, 0x2, 0x2, 0x57, 0x58, 0x7, 
    0x5, 0x2, 0x2, 0x58, 0x59, 0x7, 0x28, 0x2, 0x2, 0x59, 0x5b, 0x7, 0x6, 
    0x2, 0x2, 0x5a, 0x57, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5e, 0x3, 0x2, 0x2, 
    0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x5d, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5f, 
    0x60, 0x7, 0x17, 0x2, 0x2, 0x60, 0x61, 0x5, 0xc, 0x7, 0x2, 0x61, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x62, 0x70, 0x5, 0x22, 0x12, 0x2, 0x63, 0x6c, 0x7, 
    0x7, 0x2, 0x2, 0x64, 0x69, 0x5, 0xc, 0x7, 0x2, 0x65, 0x66, 0x7, 0xa, 
    0x2, 0x2, 0x66, 0x68, 0x5, 0xc, 0x7, 0x2, 0x67, 0x65, 0x3, 0x2, 0x2, 
    0x2, 0x68, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 
    0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6b, 
    0x69, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x64, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 
    0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x70, 0x7, 
    0x8, 0x2, 0x2, 0x6f, 0x62, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x63, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0xd, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x5, 0x8, 0x5, 
    0x2, 0x72, 0x77, 0x5, 0x10, 0x9, 0x2, 0x73, 0x74, 0x7, 0xa, 0x2, 0x2, 
    0x74, 0x76, 0x5, 0x10, 0x9, 0x2, 0x75, 0x73, 0x3, 0x2, 0x2, 0x2, 0x76, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x77, 0x75, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x79, 0x77, 0x3, 
    0x2, 0x2, 0x2, 0x7a, 0x7b, 0x7, 0x9, 0x2, 0x2, 0x7b, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x7c, 0x82, 0x7, 0x27, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x5, 0x2, 
    0x2, 0x7e, 0x7f, 0x7, 0x28, 0x2, 0x2, 0x7f, 0x81, 0x7, 0x6, 0x2, 0x2, 
    0x80, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 0x3, 0x2, 0x2, 0x2, 0x82, 
    0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 0x2, 0x83, 0x87, 
    0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 0x85, 0x86, 0x7, 
    0x17, 0x2, 0x2, 0x86, 0x88, 0x5, 0xc, 0x7, 0x2, 0x87, 0x85, 0x3, 0x2, 
    0x2, 0x2, 0x87, 0x88, 0x3, 0x2, 0x2, 0x2, 0x88, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x89, 0x8a, 0x5, 0x14, 0xb, 0x2, 0x8a, 0x8b, 0x7, 0x27, 0x2, 0x2, 
    0x8b, 0x8d, 0x7, 0x3, 0x2, 0x2, 0x8c, 0x8e, 0x5, 0x16, 0xc, 0x2, 0x8d, 
    0x8c, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 
    0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 0x7, 0x4, 0x2, 0x2, 0x90, 0x91, 0x5, 
    0x1a, 0xe, 0x2, 0x91, 0x13, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x9, 0x3, 
    0x2, 0x2, 0x93, 0x15, 0x3, 0x2, 0x2, 0x2, 0x94, 0x99, 0x5, 0x18, 0xd, 
    0x2, 0x95, 0x96, 0x7, 0xa, 0x2, 0x2, 0x96, 0x98, 0x5, 0x18, 0xd, 0x2, 
    0x97, 0x95, 0x3, 0x2, 0x2, 0x2, 0x98, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x99, 
    0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x9b, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x5, 
    0x8, 0x5, 0x2, 0x9d, 0xab, 0x7, 0x27, 0x2, 0x2, 0x9e, 0xa0, 0x7, 0x5, 
    0x2, 0x2, 0x9f, 0xa1, 0x7, 0x28, 0x2, 0x2, 0xa0, 0x9f, 0x3, 0x2, 0x2, 
    0x2, 0xa0, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 0x2, 0x2, 0x2, 
    0xa2, 0xa8, 0x7, 0x6, 0x2, 0x2, 0xa3, 0xa4, 0x7, 0x5, 0x2, 0x2, 0xa4, 
    0xa5, 0x7, 0x28, 0x2, 0x2, 0xa5, 0xa7, 0x7, 0x6, 0x2, 0x2, 0xa6, 0xa3, 
    0x3, 0x2, 0x2, 0x2, 0xa7, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa6, 0x3, 
    0x2, 0x2, 0x2, 0xa8, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xac, 0x3, 0x2, 
    0x2, 0x2, 0xaa, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xab, 0x9e, 0x3, 0x2, 0x2, 
    0x2, 0xab, 0xac, 0x3, 0x2, 0x2, 0x2, 0xac, 0x19, 0x3, 0x2, 0x2, 0x2, 
    0xad, 0xb1, 0x7, 0x7, 0x2, 0x2, 0xae, 0xb0, 0x5, 0x1c, 0xf, 0x2, 0xaf, 
    0xae, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xaf, 
    0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb4, 0x3, 
    0x2, 0x2, 0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0x8, 
    0x2, 0x2, 0xb5, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb9, 0x5, 0x4, 0x3, 
    0x2, 0xb7, 0xb9, 0x5, 0x1e, 0x10, 0x2, 0xb8, 0xb6, 0x3, 0x2, 0x2, 0x2, 
    0xb8, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xb9, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xba, 
    0xbb, 0x5, 0x26, 0x14, 0x2, 0xbb, 0xbc, 0x7, 0x17, 0x2, 0x2, 0xbc, 0xbd, 
    0x5, 0x20, 0x11, 0x2, 0xbd, 0xbe, 0x7, 0x9, 0x2, 0x2, 0xbe, 0xdb, 0x3, 
    0x2, 0x2, 0x2, 0xbf, 0xc1, 0x5, 0x20, 0x11, 0x2, 0xc0, 0xbf, 0x3, 0x2, 
    0x2, 0x2, 0xc0, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x3, 0x2, 0x2, 
    0x2, 0xc2, 0xdb, 0x7, 0x9, 0x2, 0x2, 0xc3, 0xdb, 0x5, 0x1a, 0xe, 0x2, 
    0xc4, 0xc5, 0x7, 0x11, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0x3, 0x2, 0x2, 0xc6, 
    0xc7, 0x5, 0x24, 0x13, 0x2, 0xc7, 0xc8, 0x7, 0x4, 0x2, 0x2, 0xc8, 0xcb, 
    0x5, 0x1e, 0x10, 0x2, 0xc9, 0xca, 0x7, 0x12, 0x2, 0x2, 0xca, 0xcc, 0x5, 
    0x1e, 0x10, 0x2, 0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 
    0x2, 0x2, 0xcc, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x7, 0x13, 0x2, 
    0x2, 0xce, 0xcf, 0x7, 0x3, 0x2, 0x2, 0xcf, 0xd0, 0x5, 0x24, 0x13, 0x2, 
    0xd0, 0xd1, 0x7, 0x4, 0x2, 0x2, 0xd1, 0xd2, 0x5, 0x1e, 0x10, 0x2, 0xd2, 
    0xdb, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd8, 0x7, 0x14, 0x2, 0x2, 0xd4, 0xd8, 
    0x7, 0x15, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0x16, 0x2, 0x2, 0xd6, 0xd8, 0x5, 
    0x20, 0x11, 0x2, 0xd7, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd4, 0x3, 0x2, 
    0x2, 0x2, 0xd7, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x3, 0x2, 0x2, 
    0x2, 0xd9, 0xdb, 0x7, 0x9, 0x2, 0x2, 0xda, 0xba, 0x3, 0x2, 0x2, 0x2, 
    0xda, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xda, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xda, 
    0xc4, 0x3, 0x2, 0x2, 0x2, 0xda, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xda, 0xd7, 
    0x3, 0x2, 0x2, 0x2, 0xdb, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdf, 0x7, 
    0x26, 0x2, 0x2, 0xdd, 0xdf, 0x5, 0x32, 0x1a, 0x2, 0xde, 0xdc, 0x3, 0x2, 
    0x2, 0x2, 0xde, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xdf, 0x21, 0x3, 0x2, 0x2, 
    0x2, 0xe0, 0xe3, 0x5, 0x2a, 0x16, 0x2, 0xe1, 0xe3, 0x7, 0x26, 0x2, 0x2, 
    0xe2, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe3, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe5, 0x5, 0x3a, 0x1e, 0x2, 0xe5, 0x25, 
    0x3, 0x2, 0x2, 0x2, 0xe6, 0xed, 0x7, 0x27, 0x2, 0x2, 0xe7, 0xe8, 0x7, 
    0x5, 0x2, 0x2, 0xe8, 0xe9, 0x5, 0x20, 0x11, 0x2, 0xe9, 0xea, 0x7, 0x6, 
    0x2, 0x2, 0xea, 0xec, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe7, 0x3, 0x2, 0x2, 
    0x2, 0xec, 0xef, 0x3, 0x2, 0x2, 0x2, 0xed, 0xeb, 0x3, 0x2, 0x2, 0x2, 
    0xed, 0xee, 0x3, 0x2, 0x2, 0x2, 0xee, 0x27, 0x3, 0x2, 0x2, 0x2, 0xef, 
    0xed, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf7, 0x5, 0x2a, 0x16, 0x2, 0xf1, 0xf7, 
    0x5, 0x26, 0x14, 0x2, 0xf2, 0xf3, 0x7, 0x3, 0x2, 0x2, 0xf3, 0xf4, 0x5, 
    0x20, 0x11, 0x2, 0xf4, 0xf5, 0x7, 0x4, 0x2, 0x2, 0xf5, 0xf7, 0x3, 0x2, 
    0x2, 0x2, 0xf6, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf1, 0x3, 0x2, 0x2, 
    0x2, 0xf6, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf7, 0x29, 0x3, 0x2, 0x2, 0x2, 
    0xf8, 0xf9, 0x9, 0x4, 0x2, 0x2, 0xf9, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xfa, 
    0x104, 0x5, 0x28, 0x15, 0x2, 0xfb, 0xfc, 0x9, 0x5, 0x2, 0x2, 0xfc, 0x104, 
    0x5, 0x2c, 0x17, 0x2, 0xfd, 0xfe, 0x7, 0x27, 0x2, 0x2, 0xfe, 0x100, 
    0x7, 0x3, 0x2, 0x2, 0xff, 0x101, 0x5, 0x2e, 0x18, 0x2, 0x100, 0xff, 
    0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 
    0x3, 0x2, 0x2, 0x2, 0x102, 0x104, 0x7, 0x4, 0x2, 0x2, 0x103, 0xfa, 0x3, 
    0x2, 0x2, 0x2, 0x103, 0xfb, 0x3, 0x2, 0x2, 0x2, 0x103, 0xfd, 0x3, 0x2, 
    0x2, 0x2, 0x104, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x105, 0x10a, 0x5, 0x20, 
    0x11, 0x2, 0x106, 0x107, 0x7, 0xa, 0x2, 0x2, 0x107, 0x109, 0x5, 0x20, 
    0x11, 0x2, 0x108, 0x106, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10c, 0x3, 0x2, 
    0x2, 0x2, 0x10a, 0x108, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10b, 0x3, 0x2, 
    0x2, 0x2, 0x10b, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10a, 0x3, 0x2, 0x2, 
    0x2, 0x10d, 0x10e, 0x8, 0x19, 0x1, 0x2, 0x10e, 0x10f, 0x5, 0x2c, 0x17, 
    0x2, 0x10f, 0x115, 0x3, 0x2, 0x2, 0x2, 0x110, 0x111, 0xc, 0x3, 0x2, 
    0x2, 0x111, 0x112, 0x9, 0x6, 0x2, 0x2, 0x112, 0x114, 0x5, 0x2c, 0x17, 
    0x2, 0x113, 0x110, 0x3, 0x2, 0x2, 0x2, 0x114, 0x117, 0x3, 0x2, 0x2, 
    0x2, 0x115, 0x113, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0x3, 0x2, 0x2, 
    0x2, 0x116, 0x31, 0x3, 0x2, 0x2, 0x2, 0x117, 0x115, 0x3, 0x2, 0x2, 0x2, 
    0x118, 0x119, 0x8, 0x1a, 0x1, 0x2, 0x119, 0x11a, 0x5, 0x30, 0x19, 0x2, 
    0x11a, 0x120, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11c, 0xc, 0x3, 0x2, 0x2, 
    0x11c, 0x11d, 0x9, 0x7, 0x2, 0x2, 0x11d, 0x11f, 0x5, 0x30, 0x19, 0x2, 
    0x11e, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x122, 0x3, 0x2, 0x2, 0x2, 
    0x120, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x120, 0x121, 0x3, 0x2, 0x2, 0x2, 
    0x121, 0x33, 0x3, 0x2, 0x2, 0x2, 0x122, 0x120, 0x3, 0x2, 0x2, 0x2, 0x123, 
    0x124, 0x8, 0x1b, 0x1, 0x2, 0x124, 0x127, 0x5, 0x32, 0x1a, 0x2, 0x125, 
    0x127, 0x7, 0x26, 0x2, 0x2, 0x126, 0x123, 0x3, 0x2, 0x2, 0x2, 0x126, 
    0x125, 0x3, 0x2, 0x2, 0x2, 0x127, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x128, 
    0x129, 0xc, 0x4, 0x2, 0x2, 0x129, 0x12a, 0x9, 0x8, 0x2, 0x2, 0x12a, 
    0x12c, 0x5, 0x32, 0x1a, 0x2, 0x12b, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12c, 
    0x12f, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12d, 
    0x12e, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x35, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x12d, 
    0x3, 0x2, 0x2, 0x2, 0x130, 0x131, 0x8, 0x1c, 0x1, 0x2, 0x131, 0x132, 
    0x5, 0x34, 0x1b, 0x2, 0x132, 0x138, 0x3, 0x2, 0x2, 0x2, 0x133, 0x134, 
    0xc, 0x3, 0x2, 0x2, 0x134, 0x135, 0x9, 0x9, 0x2, 0x2, 0x135, 0x137, 
    0x5, 0x34, 0x1b, 0x2, 0x136, 0x133, 0x3, 0x2, 0x2, 0x2, 0x137, 0x13a, 
    0x3, 0x2, 0x2, 0x2, 0x138, 0x136, 0x3, 0x2, 0x2, 0x2, 0x138, 0x139, 
    0x3, 0x2, 0x2, 0x2, 0x139, 0x37, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x138, 0x3, 
    0x2, 0x2, 0x2, 0x13b, 0x13c, 0x8, 0x1d, 0x1, 0x2, 0x13c, 0x13d, 0x5, 
    0x36, 0x1c, 0x2, 0x13d, 0x143, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x13f, 0xc, 
    0x3, 0x2, 0x2, 0x13f, 0x140, 0x7, 0x24, 0x2, 0x2, 0x140, 0x142, 0x5, 
    0x36, 0x1c, 0x2, 0x141, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x142, 0x145, 0x3, 
    0x2, 0x2, 0x2, 0x143, 0x141, 0x3, 0x2, 0x2, 0x2, 0x143, 0x144, 0x3, 
    0x2, 0x2, 0x2, 0x144, 0x39, 0x3, 0x2, 0x2, 0x2, 0x145, 0x143, 0x3, 0x2, 
    0x2, 0x2, 0x146, 0x147, 0x8, 0x1e, 0x1, 0x2, 0x147, 0x148, 0x5, 0x38, 
    0x1d, 0x2, 0x148, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14a, 0xc, 0x3, 
    0x2, 0x2, 0x14a, 0x14b, 0x7, 0x25, 0x2, 0x2, 0x14b, 0x14d, 0x5, 0x38, 
    0x1d, 0x2, 0x14c, 0x149, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x150, 0x3, 0x2, 
    0x2, 0x2, 0x14e, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x3, 0x2, 
    0x2, 0x2, 0x14f, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x150, 0x14e, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0x3e, 0x40, 0x46, 0x4f, 0x5c, 0x69, 0x6c, 0x6f, 0x77, 0x82, 
    0x87, 0x8d, 0x99, 0xa0, 0xa8, 0xab, 0xb1, 0xb8, 0xc0, 0xcb, 0xd7, 0xda, 
    0xde, 0xe2, 0xed, 0xf6, 0x100, 0x103, 0x10a, 0x115, 0x120, 0x126, 0x12d, 
    0x138, 0x143, 0x14e, 
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
