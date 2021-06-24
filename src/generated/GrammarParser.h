
// Generated from D:/Slag/neolang/src/Parser/grammar/Grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"




class  GrammarParser : public antlr4::Parser {
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

  enum {
    RuleCompilationUnit = 0, RuleClassDeclaration = 1, RuleField = 2, RuleMethodDeclaration = 3, 
    RuleInstructionsDecl = 4, RuleInstruction = 5, RuleCall = 6, RuleIfBlock = 7, 
    RuleElseBlock = 8, RuleInstructionsWithOp = 9
  };

  explicit GrammarParser(antlr4::TokenStream *input);
  ~GrammarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class CompilationUnitContext;
  class ClassDeclarationContext;
  class FieldContext;
  class MethodDeclarationContext;
  class InstructionsDeclContext;
  class InstructionContext;
  class CallContext;
  class IfBlockContext;
  class ElseBlockContext;
  class InstructionsWithOpContext; 

  class  CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ClassDeclarationContext *classDeclaration();
    antlr4::tree::TerminalNode *EOF();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompilationUnitContext* compilationUnit();

  class  ClassDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ClassDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CLASS();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<FieldContext *> field();
    FieldContext* field(size_t i);
    std::vector<MethodDeclarationContext *> methodDeclaration();
    MethodDeclarationContext* methodDeclaration(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassDeclarationContext* classDeclaration();

  class  FieldContext : public antlr4::ParserRuleContext {
  public:
    FieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FIELD();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldContext* field();

  class  MethodDeclarationContext : public antlr4::ParserRuleContext {
  public:
    MethodDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEF();
    antlr4::tree::TerminalNode *IDENTIFIER();
    InstructionsDeclContext *instructionsDecl();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MethodDeclarationContext* methodDeclaration();

  class  InstructionsDeclContext : public antlr4::ParserRuleContext {
  public:
    InstructionsDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InstructionContext *instruction();
    InstructionsDeclContext *instructionsDecl();
    IfBlockContext *ifBlock();
    ElseBlockContext *elseBlock();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InstructionsDeclContext* instructionsDecl();

  class  InstructionContext : public antlr4::ParserRuleContext {
  public:
    InstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IADD();
    antlr4::tree::TerminalNode *ISUB();
    antlr4::tree::TerminalNode *IDIV();
    antlr4::tree::TerminalNode *IMUL();
    antlr4::tree::TerminalNode *IRET();
    antlr4::tree::TerminalNode *FADD();
    antlr4::tree::TerminalNode *FSUB();
    antlr4::tree::TerminalNode *FDIV();
    antlr4::tree::TerminalNode *FMUL();
    antlr4::tree::TerminalNode *FRET();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *NEW();
    antlr4::tree::TerminalNode *CMPEQ();
    antlr4::tree::TerminalNode *SWAP();
    antlr4::tree::TerminalNode *RET();
    CallContext *call();
    InstructionsWithOpContext *instructionsWithOp();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InstructionContext* instruction();

  class  CallContext : public antlr4::ParserRuleContext {
  public:
    CallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CALL();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallContext* call();

  class  IfBlockContext : public antlr4::ParserRuleContext {
  public:
    IfBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    InstructionsDeclContext *instructionsDecl();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfBlockContext* ifBlock();

  class  ElseBlockContext : public antlr4::ParserRuleContext {
  public:
    ElseBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSE();
    InstructionsDeclContext *instructionsDecl();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElseBlockContext* elseBlock();

  class  InstructionsWithOpContext : public antlr4::ParserRuleContext {
  public:
    InstructionsWithOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IPUSH();
    antlr4::tree::TerminalNode *DECIMAL_LITERAL();
    antlr4::tree::TerminalNode *ILOAD();
    antlr4::tree::TerminalNode *ISTORE();
    antlr4::tree::TerminalNode *FPUSH();
    antlr4::tree::TerminalNode *FLOAT_LITERAL();
    antlr4::tree::TerminalNode *FLOAD();
    antlr4::tree::TerminalNode *FSTORE();
    antlr4::tree::TerminalNode *LDC();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *RSTORE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InstructionsWithOpContext* instructionsWithOp();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

