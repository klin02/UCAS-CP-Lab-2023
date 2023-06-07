
    #include "cact_types.h"
    #include "SymbolTable.h"
    #include <vector>
    #include <string>


// Generated from CACT.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  CACTLexer : public antlr4::Lexer {
public:
  enum {
    LeftParen = 1, RightParen = 2, LeftBracket = 3, RightBracket = 4, LeftBrace = 5, 
    RightBrace = 6, SEMICOLON = 7, COMMA = 8, CONST = 9, VOID = 10, INT = 11, 
    BOOL = 12, FLOAT = 13, DOUBLE = 14, IF = 15, ELSE = 16, WHILE = 17, 
    BREAK = 18, CONTINUE = 19, RETURN = 20, ASSIGN = 21, POS_ADD = 22, NEG_SUB = 23, 
    NOT = 24, MUL = 25, DIV = 26, MOD = 27, LEQ = 28, GEQ = 29, LT = 30, 
    GT = 31, EQ = 32, NEQ = 33, AND = 34, OR = 35, BoolConst = 36, Ident = 37, 
    IntConst = 38, FloatConst = 39, DoubleConst = 40, NewLine = 41, WhiteSpace = 42, 
    LineComment = 43, BlockComment = 44
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

