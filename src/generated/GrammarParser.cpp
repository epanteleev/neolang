
// Generated from D:/Slag/neolang/src/Parser/grammar/Grammar.g4 by ANTLR 4.9.1


#include "GrammarVisitor.h"

#include "GrammarParser.h"


using namespace antlrcpp;
using namespace antlr4;

GrammarParser::GrammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

GrammarParser::~GrammarParser() {
  delete _interpreter;
}

std::string GrammarParser::getGrammarFileName() const {
  return "Grammar.g4";
}

const std::vector<std::string>& GrammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& GrammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

GrammarParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ClassDeclarationContext* GrammarParser::CompilationUnitContext::classDeclaration() {
  return getRuleContext<GrammarParser::ClassDeclarationContext>(0);
}

tree::TerminalNode* GrammarParser::CompilationUnitContext::EOF() {
  return getToken(GrammarParser::EOF, 0);
}


size_t GrammarParser::CompilationUnitContext::getRuleIndex() const {
  return GrammarParser::RuleCompilationUnit;
}


antlrcpp::Any GrammarParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::CompilationUnitContext* GrammarParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, GrammarParser::RuleCompilationUnit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    classDeclaration();
    setState(19);
    match(GrammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclarationContext ------------------------------------------------------------------

GrammarParser::ClassDeclarationContext::ClassDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::ClassDeclarationContext::CLASS() {
  return getToken(GrammarParser::CLASS, 0);
}

tree::TerminalNode* GrammarParser::ClassDeclarationContext::IDENTIFIER() {
  return getToken(GrammarParser::IDENTIFIER, 0);
}

std::vector<GrammarParser::MethodDeclarationContext *> GrammarParser::ClassDeclarationContext::methodDeclaration() {
  return getRuleContexts<GrammarParser::MethodDeclarationContext>();
}

GrammarParser::MethodDeclarationContext* GrammarParser::ClassDeclarationContext::methodDeclaration(size_t i) {
  return getRuleContext<GrammarParser::MethodDeclarationContext>(i);
}


size_t GrammarParser::ClassDeclarationContext::getRuleIndex() const {
  return GrammarParser::RuleClassDeclaration;
}


antlrcpp::Any GrammarParser::ClassDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitClassDeclaration(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::ClassDeclarationContext* GrammarParser::classDeclaration() {
  ClassDeclarationContext *_localctx = _tracker.createInstance<ClassDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, GrammarParser::RuleClassDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21);
    match(GrammarParser::CLASS);
    setState(22);
    match(GrammarParser::IDENTIFIER);
    setState(23);
    match(GrammarParser::T__0);
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GrammarParser::DEF) {
      setState(24);
      methodDeclaration();
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(30);
    match(GrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodDeclarationContext ------------------------------------------------------------------

GrammarParser::MethodDeclarationContext::MethodDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::MethodDeclarationContext::DEF() {
  return getToken(GrammarParser::DEF, 0);
}

tree::TerminalNode* GrammarParser::MethodDeclarationContext::IDENTIFIER() {
  return getToken(GrammarParser::IDENTIFIER, 0);
}

GrammarParser::InstructionsDeclContext* GrammarParser::MethodDeclarationContext::instructionsDecl() {
  return getRuleContext<GrammarParser::InstructionsDeclContext>(0);
}


size_t GrammarParser::MethodDeclarationContext::getRuleIndex() const {
  return GrammarParser::RuleMethodDeclaration;
}


antlrcpp::Any GrammarParser::MethodDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitMethodDeclaration(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::MethodDeclarationContext* GrammarParser::methodDeclaration() {
  MethodDeclarationContext *_localctx = _tracker.createInstance<MethodDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, GrammarParser::RuleMethodDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    match(GrammarParser::DEF);
    setState(33);
    match(GrammarParser::IDENTIFIER);
    setState(34);
    match(GrammarParser::T__0);
    setState(35);
    instructionsDecl();
    setState(36);
    match(GrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InstructionsDeclContext ------------------------------------------------------------------

GrammarParser::InstructionsDeclContext::InstructionsDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::InstructionContext* GrammarParser::InstructionsDeclContext::instruction() {
  return getRuleContext<GrammarParser::InstructionContext>(0);
}

GrammarParser::InstructionsDeclContext* GrammarParser::InstructionsDeclContext::instructionsDecl() {
  return getRuleContext<GrammarParser::InstructionsDeclContext>(0);
}

GrammarParser::IfBlockContext* GrammarParser::InstructionsDeclContext::ifBlock() {
  return getRuleContext<GrammarParser::IfBlockContext>(0);
}

GrammarParser::ElseBlockContext* GrammarParser::InstructionsDeclContext::elseBlock() {
  return getRuleContext<GrammarParser::ElseBlockContext>(0);
}


size_t GrammarParser::InstructionsDeclContext::getRuleIndex() const {
  return GrammarParser::RuleInstructionsDecl;
}


antlrcpp::Any GrammarParser::InstructionsDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitInstructionsDecl(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::InstructionsDeclContext* GrammarParser::instructionsDecl() {
  InstructionsDeclContext *_localctx = _tracker.createInstance<InstructionsDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, GrammarParser::RuleInstructionsDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GrammarParser::IADD:
      case GrammarParser::ISUB:
      case GrammarParser::IDIV:
      case GrammarParser::IMUL:
      case GrammarParser::IPUSH:
      case GrammarParser::ILOAD:
      case GrammarParser::ISTORE:
      case GrammarParser::IRET:
      case GrammarParser::FADD:
      case GrammarParser::FSUB:
      case GrammarParser::FDIV:
      case GrammarParser::FMUL:
      case GrammarParser::FPUSH:
      case GrammarParser::FLOAD:
      case GrammarParser::FSTORE:
      case GrammarParser::FRET:
      case GrammarParser::LDC:
      case GrammarParser::SWAP:
      case GrammarParser::AND:
      case GrammarParser::OR:
      case GrammarParser::RSTORE:
      case GrammarParser::CMPEQ:
      case GrammarParser::CALL:
      case GrammarParser::RET: {
        setState(38);
        instruction();
        break;
      }

      case GrammarParser::IF: {
        setState(39);
        ifBlock();
        setState(41);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == GrammarParser::ELSE) {
          setState(40);
          elseBlock();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(46);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << GrammarParser::IADD)
      | (1ULL << GrammarParser::ISUB)
      | (1ULL << GrammarParser::IDIV)
      | (1ULL << GrammarParser::IMUL)
      | (1ULL << GrammarParser::IPUSH)
      | (1ULL << GrammarParser::ILOAD)
      | (1ULL << GrammarParser::ISTORE)
      | (1ULL << GrammarParser::IRET)
      | (1ULL << GrammarParser::FADD)
      | (1ULL << GrammarParser::FSUB)
      | (1ULL << GrammarParser::FDIV)
      | (1ULL << GrammarParser::FMUL)
      | (1ULL << GrammarParser::FPUSH)
      | (1ULL << GrammarParser::FLOAD)
      | (1ULL << GrammarParser::FSTORE)
      | (1ULL << GrammarParser::FRET)
      | (1ULL << GrammarParser::LDC)
      | (1ULL << GrammarParser::SWAP)
      | (1ULL << GrammarParser::AND)
      | (1ULL << GrammarParser::OR)
      | (1ULL << GrammarParser::RSTORE)
      | (1ULL << GrammarParser::CMPEQ)
      | (1ULL << GrammarParser::IF)
      | (1ULL << GrammarParser::CALL)
      | (1ULL << GrammarParser::RET))) != 0)) {
      setState(45);
      instructionsDecl();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InstructionContext ------------------------------------------------------------------

GrammarParser::InstructionContext::InstructionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::InstructionContext::IADD() {
  return getToken(GrammarParser::IADD, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::ISUB() {
  return getToken(GrammarParser::ISUB, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::IDIV() {
  return getToken(GrammarParser::IDIV, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::IMUL() {
  return getToken(GrammarParser::IMUL, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::IRET() {
  return getToken(GrammarParser::IRET, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::FADD() {
  return getToken(GrammarParser::FADD, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::FSUB() {
  return getToken(GrammarParser::FSUB, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::FDIV() {
  return getToken(GrammarParser::FDIV, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::FMUL() {
  return getToken(GrammarParser::FMUL, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::FRET() {
  return getToken(GrammarParser::FRET, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::OR() {
  return getToken(GrammarParser::OR, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::AND() {
  return getToken(GrammarParser::AND, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::CMPEQ() {
  return getToken(GrammarParser::CMPEQ, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::SWAP() {
  return getToken(GrammarParser::SWAP, 0);
}

tree::TerminalNode* GrammarParser::InstructionContext::RET() {
  return getToken(GrammarParser::RET, 0);
}

GrammarParser::CallContext* GrammarParser::InstructionContext::call() {
  return getRuleContext<GrammarParser::CallContext>(0);
}

GrammarParser::InstructionsWithOpContext* GrammarParser::InstructionContext::instructionsWithOp() {
  return getRuleContext<GrammarParser::InstructionsWithOpContext>(0);
}


size_t GrammarParser::InstructionContext::getRuleIndex() const {
  return GrammarParser::RuleInstruction;
}


antlrcpp::Any GrammarParser::InstructionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitInstruction(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::InstructionContext* GrammarParser::instruction() {
  InstructionContext *_localctx = _tracker.createInstance<InstructionContext>(_ctx, getState());
  enterRule(_localctx, 8, GrammarParser::RuleInstruction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(56);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GrammarParser::IADD:
      case GrammarParser::ISUB:
      case GrammarParser::IDIV:
      case GrammarParser::IMUL:
      case GrammarParser::IRET: {
        enterOuterAlt(_localctx, 1);
        setState(48);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << GrammarParser::IADD)
          | (1ULL << GrammarParser::ISUB)
          | (1ULL << GrammarParser::IDIV)
          | (1ULL << GrammarParser::IMUL)
          | (1ULL << GrammarParser::IRET))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case GrammarParser::FADD:
      case GrammarParser::FSUB:
      case GrammarParser::FDIV:
      case GrammarParser::FMUL:
      case GrammarParser::FRET: {
        enterOuterAlt(_localctx, 2);
        setState(49);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << GrammarParser::FADD)
          | (1ULL << GrammarParser::FSUB)
          | (1ULL << GrammarParser::FDIV)
          | (1ULL << GrammarParser::FMUL)
          | (1ULL << GrammarParser::FRET))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case GrammarParser::AND:
      case GrammarParser::OR: {
        enterOuterAlt(_localctx, 3);
        setState(50);
        _la = _input->LA(1);
        if (!(_la == GrammarParser::AND

        || _la == GrammarParser::OR)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case GrammarParser::CMPEQ: {
        enterOuterAlt(_localctx, 4);
        setState(51);
        match(GrammarParser::CMPEQ);
        break;
      }

      case GrammarParser::SWAP: {
        enterOuterAlt(_localctx, 5);
        setState(52);
        match(GrammarParser::SWAP);
        break;
      }

      case GrammarParser::RET: {
        enterOuterAlt(_localctx, 6);
        setState(53);
        match(GrammarParser::RET);
        break;
      }

      case GrammarParser::CALL: {
        enterOuterAlt(_localctx, 7);
        setState(54);
        call();
        break;
      }

      case GrammarParser::IPUSH:
      case GrammarParser::ILOAD:
      case GrammarParser::ISTORE:
      case GrammarParser::FPUSH:
      case GrammarParser::FLOAD:
      case GrammarParser::FSTORE:
      case GrammarParser::LDC:
      case GrammarParser::RSTORE: {
        enterOuterAlt(_localctx, 8);
        setState(55);
        instructionsWithOp();
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

//----------------- CallContext ------------------------------------------------------------------

GrammarParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::CallContext::CALL() {
  return getToken(GrammarParser::CALL, 0);
}

std::vector<tree::TerminalNode *> GrammarParser::CallContext::IDENTIFIER() {
  return getTokens(GrammarParser::IDENTIFIER);
}

tree::TerminalNode* GrammarParser::CallContext::IDENTIFIER(size_t i) {
  return getToken(GrammarParser::IDENTIFIER, i);
}


size_t GrammarParser::CallContext::getRuleIndex() const {
  return GrammarParser::RuleCall;
}


antlrcpp::Any GrammarParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::CallContext* GrammarParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 10, GrammarParser::RuleCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(GrammarParser::CALL);
    setState(59);
    match(GrammarParser::IDENTIFIER);
    setState(60);
    match(GrammarParser::T__2);
    setState(61);
    match(GrammarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfBlockContext ------------------------------------------------------------------

GrammarParser::IfBlockContext::IfBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::IfBlockContext::IF() {
  return getToken(GrammarParser::IF, 0);
}

GrammarParser::InstructionsDeclContext* GrammarParser::IfBlockContext::instructionsDecl() {
  return getRuleContext<GrammarParser::InstructionsDeclContext>(0);
}


size_t GrammarParser::IfBlockContext::getRuleIndex() const {
  return GrammarParser::RuleIfBlock;
}


antlrcpp::Any GrammarParser::IfBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitIfBlock(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::IfBlockContext* GrammarParser::ifBlock() {
  IfBlockContext *_localctx = _tracker.createInstance<IfBlockContext>(_ctx, getState());
  enterRule(_localctx, 12, GrammarParser::RuleIfBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(GrammarParser::IF);
    setState(64);
    match(GrammarParser::T__0);
    setState(65);
    instructionsDecl();
    setState(66);
    match(GrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseBlockContext ------------------------------------------------------------------

GrammarParser::ElseBlockContext::ElseBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::ElseBlockContext::ELSE() {
  return getToken(GrammarParser::ELSE, 0);
}

GrammarParser::InstructionsDeclContext* GrammarParser::ElseBlockContext::instructionsDecl() {
  return getRuleContext<GrammarParser::InstructionsDeclContext>(0);
}


size_t GrammarParser::ElseBlockContext::getRuleIndex() const {
  return GrammarParser::RuleElseBlock;
}


antlrcpp::Any GrammarParser::ElseBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitElseBlock(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::ElseBlockContext* GrammarParser::elseBlock() {
  ElseBlockContext *_localctx = _tracker.createInstance<ElseBlockContext>(_ctx, getState());
  enterRule(_localctx, 14, GrammarParser::RuleElseBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(GrammarParser::ELSE);
    setState(69);
    match(GrammarParser::T__0);
    setState(70);
    instructionsDecl();
    setState(71);
    match(GrammarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InstructionsWithOpContext ------------------------------------------------------------------

GrammarParser::InstructionsWithOpContext::InstructionsWithOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::IPUSH() {
  return getToken(GrammarParser::IPUSH, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::DECIMAL_LITERAL() {
  return getToken(GrammarParser::DECIMAL_LITERAL, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::ILOAD() {
  return getToken(GrammarParser::ILOAD, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::ISTORE() {
  return getToken(GrammarParser::ISTORE, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::FPUSH() {
  return getToken(GrammarParser::FPUSH, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::FLOAT_LITERAL() {
  return getToken(GrammarParser::FLOAT_LITERAL, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::FLOAD() {
  return getToken(GrammarParser::FLOAD, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::FSTORE() {
  return getToken(GrammarParser::FSTORE, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::LDC() {
  return getToken(GrammarParser::LDC, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::STRING_LITERAL() {
  return getToken(GrammarParser::STRING_LITERAL, 0);
}

tree::TerminalNode* GrammarParser::InstructionsWithOpContext::RSTORE() {
  return getToken(GrammarParser::RSTORE, 0);
}


size_t GrammarParser::InstructionsWithOpContext::getRuleIndex() const {
  return GrammarParser::RuleInstructionsWithOp;
}


antlrcpp::Any GrammarParser::InstructionsWithOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<GrammarVisitor*>(visitor))
    return parserVisitor->visitInstructionsWithOp(this);
  else
    return visitor->visitChildren(this);
}

GrammarParser::InstructionsWithOpContext* GrammarParser::instructionsWithOp() {
  InstructionsWithOpContext *_localctx = _tracker.createInstance<InstructionsWithOpContext>(_ctx, getState());
  enterRule(_localctx, 16, GrammarParser::RuleInstructionsWithOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(89);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GrammarParser::IPUSH: {
        enterOuterAlt(_localctx, 1);
        setState(73);
        match(GrammarParser::IPUSH);
        setState(74);
        match(GrammarParser::DECIMAL_LITERAL);
        break;
      }

      case GrammarParser::ILOAD: {
        enterOuterAlt(_localctx, 2);
        setState(75);
        match(GrammarParser::ILOAD);
        setState(76);
        match(GrammarParser::DECIMAL_LITERAL);
        break;
      }

      case GrammarParser::ISTORE: {
        enterOuterAlt(_localctx, 3);
        setState(77);
        match(GrammarParser::ISTORE);
        setState(78);
        match(GrammarParser::DECIMAL_LITERAL);
        break;
      }

      case GrammarParser::FPUSH: {
        enterOuterAlt(_localctx, 4);
        setState(79);
        match(GrammarParser::FPUSH);
        setState(80);
        match(GrammarParser::FLOAT_LITERAL);
        break;
      }

      case GrammarParser::FLOAD: {
        enterOuterAlt(_localctx, 5);
        setState(81);
        match(GrammarParser::FLOAD);
        setState(82);
        match(GrammarParser::DECIMAL_LITERAL);
        break;
      }

      case GrammarParser::FSTORE: {
        enterOuterAlt(_localctx, 6);
        setState(83);
        match(GrammarParser::FSTORE);
        setState(84);
        match(GrammarParser::DECIMAL_LITERAL);
        break;
      }

      case GrammarParser::LDC: {
        enterOuterAlt(_localctx, 7);
        setState(85);
        match(GrammarParser::LDC);
        setState(86);
        match(GrammarParser::STRING_LITERAL);
        break;
      }

      case GrammarParser::RSTORE: {
        enterOuterAlt(_localctx, 8);
        setState(87);
        match(GrammarParser::RSTORE);
        setState(88);
        match(GrammarParser::DECIMAL_LITERAL);
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

// Static vars and initialization.
std::vector<dfa::DFA> GrammarParser::_decisionToDFA;
atn::PredictionContextCache GrammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN GrammarParser::_atn;
std::vector<uint16_t> GrammarParser::_serializedATN;

std::vector<std::string> GrammarParser::_ruleNames = {
  "compilationUnit", "classDeclaration", "methodDeclaration", "instructionsDecl", 
  "instruction", "call", "ifBlock", "elseBlock", "instructionsWithOp"
};

std::vector<std::string> GrammarParser::_literalNames = {
  "", "'{'", "'}'", "'::'", "'iadd'", "'isub'", "'idiv'", "'imul'", "'ipush'", 
  "'ipop'", "'iload'", "'istore'", "'iret'", "'fadd'", "'fsub'", "'fdiv'", 
  "'fmul'", "'fpush'", "'fpop'", "'fload'", "'fstore'", "'fret'", "'ldc'", 
  "'swap'", "'and'", "'or'", "'rstore'", "'cmpeq'", "'class'", "'def'", 
  "'if'", "'else'", "'call'", "'ret'", "", "", "' '"
};

std::vector<std::string> GrammarParser::_symbolicNames = {
  "", "", "", "", "IADD", "ISUB", "IDIV", "IMUL", "IPUSH", "IPOP", "ILOAD", 
  "ISTORE", "IRET", "FADD", "FSUB", "FDIV", "FMUL", "FPUSH", "FPOP", "FLOAD", 
  "FSTORE", "FRET", "LDC", "SWAP", "AND", "OR", "RSTORE", "CMPEQ", "CLASS", 
  "DEF", "IF", "ELSE", "CALL", "RET", "NEWLINE", "TAB", "WHITESPACE", "DECIMAL_LITERAL", 
  "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "IDENTIFIER"
};

dfa::Vocabulary GrammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> GrammarParser::_tokenNames;

GrammarParser::Initializer::Initializer() {
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
    0x3, 0x2c, 0x5e, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x1c, 
    0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1f, 0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x5, 0x5, 0x2c, 0xa, 0x5, 0x5, 0x5, 0x2e, 0xa, 0x5, 0x3, 
    0x5, 0x5, 0x5, 0x31, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x3b, 0xa, 0x6, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x5c, 0xa, 0xa, 0x3, 0xa, 0x2, 0x2, 
    0xb, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x2, 0x5, 0x4, 0x2, 
    0x6, 0x9, 0xe, 0xe, 0x4, 0x2, 0xf, 0x12, 0x17, 0x17, 0x3, 0x2, 0x1a, 
    0x1b, 0x2, 0x66, 0x2, 0x14, 0x3, 0x2, 0x2, 0x2, 0x4, 0x17, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x22, 0x3, 0x2, 0x2, 0x2, 0x8, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x3a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3c, 0x3, 0x2, 0x2, 0x2, 0xe, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x46, 0x3, 0x2, 0x2, 0x2, 0x12, 0x5b, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x15, 0x5, 0x4, 0x3, 0x2, 0x15, 0x16, 0x7, 0x2, 
    0x2, 0x3, 0x16, 0x3, 0x3, 0x2, 0x2, 0x2, 0x17, 0x18, 0x7, 0x1e, 0x2, 
    0x2, 0x18, 0x19, 0x7, 0x2c, 0x2, 0x2, 0x19, 0x1d, 0x7, 0x3, 0x2, 0x2, 
    0x1a, 0x1c, 0x5, 0x6, 0x4, 0x2, 0x1b, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 
    0x3, 0x2, 0x2, 0x2, 0x1e, 0x20, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x1d, 0x3, 
    0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 0x4, 0x2, 0x2, 0x21, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0x23, 0x7, 0x1f, 0x2, 0x2, 0x23, 0x24, 0x7, 0x2c, 0x2, 
    0x2, 0x24, 0x25, 0x7, 0x3, 0x2, 0x2, 0x25, 0x26, 0x5, 0x8, 0x5, 0x2, 
    0x26, 0x27, 0x7, 0x4, 0x2, 0x2, 0x27, 0x7, 0x3, 0x2, 0x2, 0x2, 0x28, 
    0x2e, 0x5, 0xa, 0x6, 0x2, 0x29, 0x2b, 0x5, 0xe, 0x8, 0x2, 0x2a, 0x2c, 
    0x5, 0x10, 0x9, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x28, 0x3, 0x2, 
    0x2, 0x2, 0x2d, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x30, 0x3, 0x2, 0x2, 
    0x2, 0x2f, 0x31, 0x5, 0x8, 0x5, 0x2, 0x30, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 0x31, 0x9, 0x3, 0x2, 0x2, 0x2, 0x32, 
    0x3b, 0x9, 0x2, 0x2, 0x2, 0x33, 0x3b, 0x9, 0x3, 0x2, 0x2, 0x34, 0x3b, 
    0x9, 0x4, 0x2, 0x2, 0x35, 0x3b, 0x7, 0x1d, 0x2, 0x2, 0x36, 0x3b, 0x7, 
    0x19, 0x2, 0x2, 0x37, 0x3b, 0x7, 0x23, 0x2, 0x2, 0x38, 0x3b, 0x5, 0xc, 
    0x7, 0x2, 0x39, 0x3b, 0x5, 0x12, 0xa, 0x2, 0x3a, 0x32, 0x3, 0x2, 0x2, 
    0x2, 0x3a, 0x33, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x34, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0x35, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x36, 0x3, 0x2, 0x2, 0x2, 0x3a, 
    0x37, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0x3b, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x7, 
    0x22, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x2c, 0x2, 0x2, 0x3e, 0x3f, 0x7, 0x5, 
    0x2, 0x2, 0x3f, 0x40, 0x7, 0x2c, 0x2, 0x2, 0x40, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x41, 0x42, 0x7, 0x20, 0x2, 0x2, 0x42, 0x43, 0x7, 0x3, 0x2, 0x2, 
    0x43, 0x44, 0x5, 0x8, 0x5, 0x2, 0x44, 0x45, 0x7, 0x4, 0x2, 0x2, 0x45, 
    0xf, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x7, 0x21, 0x2, 0x2, 0x47, 0x48, 
    0x7, 0x3, 0x2, 0x2, 0x48, 0x49, 0x5, 0x8, 0x5, 0x2, 0x49, 0x4a, 0x7, 
    0x4, 0x2, 0x2, 0x4a, 0x11, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0xa, 
    0x2, 0x2, 0x4c, 0x5c, 0x7, 0x27, 0x2, 0x2, 0x4d, 0x4e, 0x7, 0xc, 0x2, 
    0x2, 0x4e, 0x5c, 0x7, 0x27, 0x2, 0x2, 0x4f, 0x50, 0x7, 0xd, 0x2, 0x2, 
    0x50, 0x5c, 0x7, 0x27, 0x2, 0x2, 0x51, 0x52, 0x7, 0x13, 0x2, 0x2, 0x52, 
    0x5c, 0x7, 0x28, 0x2, 0x2, 0x53, 0x54, 0x7, 0x15, 0x2, 0x2, 0x54, 0x5c, 
    0x7, 0x27, 0x2, 0x2, 0x55, 0x56, 0x7, 0x16, 0x2, 0x2, 0x56, 0x5c, 0x7, 
    0x27, 0x2, 0x2, 0x57, 0x58, 0x7, 0x18, 0x2, 0x2, 0x58, 0x5c, 0x7, 0x2b, 
    0x2, 0x2, 0x59, 0x5a, 0x7, 0x1c, 0x2, 0x2, 0x5a, 0x5c, 0x7, 0x27, 0x2, 
    0x2, 0x5b, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x4d, 0x3, 0x2, 0x2, 0x2, 
    0x5b, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x51, 0x3, 0x2, 0x2, 0x2, 0x5b, 
    0x53, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x55, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x57, 
    0x3, 0x2, 0x2, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0x8, 0x1d, 0x2b, 0x2d, 0x30, 0x3a, 0x5b, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

GrammarParser::Initializer GrammarParser::_init;
