#include <string>
#include <Vm/Vm.h>
#include "antlr4-runtime.h"
#include "generated/GrammarBaseVisitor.h"

class VisitorImpl : public GrammarBaseVisitor {
public:
    explicit VisitorImpl(Vm &vm) : m_vm(vm) {}

    antlrcpp::Any visitCompilationUnit(GrammarParser::CompilationUnitContext *ctx) override;

    antlrcpp::Any visitClassDeclaration(GrammarParser::ClassDeclarationContext *ctx) override;

    std::unique_ptr<ObjMethod> visitMethodDeclarationOverride(GrammarParser::MethodDeclarationContext *ctx);

    antlrcpp::Any visitInstructionsDecl(GrammarParser::InstructionsDeclContext *ctx) override;

    antlrcpp::Any visitInstruction(GrammarParser::InstructionContext *ctx) override;

    antlrcpp::Any visitInstructionsWithOp(GrammarParser::InstructionsWithOpContext *ctx) override;

    antlrcpp::Any visitCall(GrammarParser::CallContext *ctx) override;

    antlrcpp::Any visitIfBlock(GrammarParser::IfBlockContext *ctx) override;

    antlrcpp::Any visitElseBlock(GrammarParser::ElseBlockContext *ctx) override;

private:
    Vm &m_vm;
};

