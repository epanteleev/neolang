
// Generated from D:/Slag/neolang/src/Parser/grammar/Grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"




class  GrammarLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, IADD = 4, ISUB = 5, IDIV = 6, IMUL = 7, 
    IPUSH = 8, IPOP = 9, ILOAD = 10, ISTORE = 11, IRET = 12, FADD = 13, 
    FSUB = 14, FDIV = 15, FMUL = 16, FPUSH = 17, FPOP = 18, FLOAD = 19, 
    FSTORE = 20, FRET = 21, LDC = 22, SWAP = 23, AND = 24, OR = 25, RSTORE = 26, 
    CMPEQ = 27, CLASS = 28, DEF = 29, IF = 30, ELSE = 31, CALL = 32, RET = 33, 
    NEWLINE = 34, TAB = 35, WHITESPACE = 36, DECIMAL_LITERAL = 37, FLOAT_LITERAL = 38, 
    BOOL_LITERAL = 39, CHAR_LITERAL = 40, STRING_LITERAL = 41, IDENTIFIER = 42
  };

  explicit GrammarLexer(antlr4::CharStream *input);
  ~GrammarLexer();

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

