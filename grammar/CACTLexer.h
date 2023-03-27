
    #include <vector>


// Generated from CACT.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  CACTLexer : public antlr4::Lexer {
public:
  enum {
    Ident = 1, BoolConst = 2, IntConst = 3, FloatConst = 4, DoubleConst = 5, 
    LeftParen = 6, RightParen = 7, LeftBracket = 8, RightBracket = 9, LeftBrace = 10, 
    RightBrace = 11, SEMICOLON = 12, COMMA = 13, TRUE = 14, FALSE = 15, 
    CONST = 16, VOID = 17, INT = 18, BOOL = 19, FLOAT = 20, DOUBLE = 21, 
    IF = 22, ELSE = 23, WHILE = 24, BREAK = 25, CONTINUE = 26, RETURN = 27, 
    ASSIGN = 28, ADD = 29, SUB = 30, NOT = 31, MUL = 32, DIV = 33, MOD = 34, 
    LEQ = 35, GEQ = 36, LT = 37, GT = 38, EQ = 39, NEQ = 40, AND = 41, OR = 42, 
    NewLine = 43, WhiteSpace = 44, LineComment = 45, BlockComment = 46
  };

  CACTLexer(antlr4::CharStream *input);
  ~CACTLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

