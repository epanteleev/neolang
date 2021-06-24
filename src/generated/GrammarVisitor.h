
// Generated from D:/Slag/neolang/src/Parser/grammar/Grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"
#include "GrammarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by GrammarParser.
 */
class  GrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by GrammarParser.
   */
    virtual antlrcpp::Any visitCompilationUnit(GrammarParser::CompilationUnitContext *context) = 0;

    virtual antlrcpp::Any visitClassDeclaration(GrammarParser::ClassDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitField(GrammarParser::FieldContext *context) = 0;

    virtual antlrcpp::Any visitMethodDeclaration(GrammarParser::MethodDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitInstructionsDecl(GrammarParser::InstructionsDeclContext *context) = 0;

    virtual antlrcpp::Any visitInstruction(GrammarParser::InstructionContext *context) = 0;

    virtual antlrcpp::Any visitCall(GrammarParser::CallContext *context) = 0;

    virtual antlrcpp::Any visitIfBlock(GrammarParser::IfBlockContext *context) = 0;

    virtual antlrcpp::Any visitElseBlock(GrammarParser::ElseBlockContext *context) = 0;

    virtual antlrcpp::Any visitInstructionsWithOp(GrammarParser::InstructionsWithOpContext *context) = 0;


};

