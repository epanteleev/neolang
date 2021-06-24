
// Generated from D:/Slag/neolang/src/Parser/grammar/Grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"




class  GrammarLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, IADD = 5, ISUB = 6, IDIV = 7, 
    IMUL = 8, IPUSH = 9, IPOP = 10, ILOAD = 11, ISTORE = 12, IRET = 13, 
    FADD = 14, FSUB = 15, FDIV = 16, FMUL = 17, FPUSH = 18, FPOP = 19, FLOAD = 20, 
    FSTORE = 21, FRET = 22, LDC = 23, SWAP = 24, NEW = 25, AND = 26, OR = 27, 
    RSTORE = 28, CMPEQ = 29, FIELD = 30, CLASS = 31, DEF = 32, IF = 33, 
    ELSE = 34, CALL = 35, RET = 36, NEWLINE = 37, TAB = 38, WHITESPACE = 39, 
    DECIMAL_LITERAL = 40, FLOAT_LITERAL = 41, BOOL_LITERAL = 42, CHAR_LITERAL = 43, 
    STRING_LITERAL = 44, IDENTIFIER = 45
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

