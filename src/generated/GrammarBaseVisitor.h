
// Generated from D:/Slag/neolang/src/Parser/grammar/Grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "GrammarVisitor.h"


/**
 * This class provides an empty implementation of GrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  GrammarBaseVisitor : public GrammarVisitor {
public:

  virtual antlrcpp::Any visitCompilationUnit(GrammarParser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassDeclaration(GrammarParser::ClassDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitField(GrammarParser::FieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMethodDeclaration(GrammarParser::MethodDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstructionsDecl(GrammarParser::InstructionsDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstruction(GrammarParser::InstructionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCall(GrammarParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfBlock(GrammarParser::IfBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseBlock(GrammarParser::ElseBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstructionsWithOp(GrammarParser::InstructionsWithOpContext *ctx) override {
    return visitChildren(ctx);
  }


};

