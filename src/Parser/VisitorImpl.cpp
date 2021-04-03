#include <generated/GrammarParser.h>
#include <generated/GrammarBaseVisitor.h>
#include "VisitorImpl.h"

antlrcpp::Any VisitorImpl::visitCompilationUnit(GrammarParser::CompilationUnitContext *ctx) {
    return visitClassDeclaration(ctx->classDeclaration());
}

antlrcpp::Any VisitorImpl::visitClassDeclaration(GrammarParser::ClassDeclarationContext *ctx) {

    auto moduleName = ObjString::from(ctx->IDENTIFIER()->toString());
    auto module = ObjModule::make(std::move(moduleName));

    auto methods = ctx->methodDeclaration();
    for (auto& i: methods) {
        module->addMethod(visitMethodDeclarationOverride(i));
    }
    m_vm.addModule(std::move(module));
    return antlrcpp::Any();
}

std::unique_ptr<ObjMethod> VisitorImpl::visitMethodDeclarationOverride(GrammarParser::MethodDeclarationContext *ctx) {
    std::string str = ctx->IDENTIFIER()->toString();
    auto methodName = ObjString::from(str);

    StreamInstruction list = visitInstructionsDecl(ctx->instructionsDecl());
    InstructionList v{std::make_move_iterator(std::begin(list)), std::make_move_iterator(std::end(list)) };
    return ObjMethod::make(std::move(methodName), std::move(v));
}

antlrcpp::Any VisitorImpl::visitInstructionsDecl(GrammarParser::InstructionsDeclContext *ctx) {
    StreamInstruction list;
    if (ctx == nullptr) {
        return list;
    }
    if (ctx->instruction() != nullptr) {
        list.push_back(visitInstruction(ctx->instruction()));
    } else if (ctx->ifBlock()) {
        StreamInstruction ifBlock = visitIfBlock(ctx->ifBlock());

        if (ctx->elseBlock()) {
            StreamInstruction elseBlock = visitElseBlock(ctx->elseBlock());

            list.emplace_back(OpCode::JUMP, Value(ifBlock.size() + 1, Type::REF));
            std::move(ifBlock.begin(), ifBlock.end(), std::back_inserter(list));

            list.emplace_back(OpCode::GOTO, Value(elseBlock.size(), Type::REF));

            std::move(elseBlock.begin(), elseBlock.end(), std::back_inserter(list));

        } else {
            list.emplace_back(OpCode::JUMP, Value(ifBlock.size(), Type::REF));
            std::move(ifBlock.begin(), ifBlock.end(), std::back_inserter(list));
        }
    }

    StreamInstruction nextList = VisitorImpl::visitInstructionsDecl(ctx->instructionsDecl());
    std::move(nextList.begin(), nextList.end(), std::back_inserter(list)); //todo
    return list;
}

antlrcpp::Any VisitorImpl::visitInstruction(GrammarParser::InstructionContext *ctx) {
    if (ctx->IADD()) {
        return Instruction(OpCode::iADD);
    } else if (ctx->ISUB()) {
        return Instruction(OpCode::iSUB);
    } else if (ctx->RET()) {
        return Instruction(OpCode::RET);
    } else if (ctx->FADD()) {
        return Instruction(OpCode::fADD);
    } else if (ctx->FSUB()) {
        return Instruction(OpCode::fSUB);
    } else if (ctx->FMUL()) {
        return Instruction(OpCode::fMUL);
    } else if (ctx->FDIV()) {
        return Instruction(OpCode::fDIV);
    } else if (ctx->FRET()) {
        return Instruction(OpCode::fRET);
    } else if (ctx->CMPEQ()) {
        return Instruction(OpCode::CMPEQ);
    }

    if (ctx->call()) {
        return visitCall(ctx->call());
    } else if (ctx->instructionsWithOp()) {
        return visitInstructionsWithOp(ctx->instructionsWithOp());
    }
    UNREACHABLE();
}

antlrcpp::Any VisitorImpl::visitInstructionsWithOp(GrammarParser::InstructionsWithOpContext *ctx) {
    if (ctx->IPUSH()) {
        return Instruction(OpCode::iPUSH, std::stoi(ctx->DECIMAL_LITERAL()->toString()));
    } else if (ctx->ILOAD()) {
        return Instruction(OpCode::iLOAD, std::stoi(ctx->DECIMAL_LITERAL()->toString()));
    } else if (ctx->ISTORE()) {
        return Instruction(OpCode::iSTORE, std::stoi(ctx->DECIMAL_LITERAL()->toString()));
    } else if (ctx->FPUSH()) {
        return Instruction(OpCode::fPUSH, std::stof(ctx->FLOAT_LITERAL()->toString()));
    } else if (ctx->FSTORE()) {
        return Instruction(OpCode::fSTORE, std::stoi(ctx->DECIMAL_LITERAL()->toString()));
    } else if (ctx->FLOAD()) {
        return Instruction(OpCode::fLOAD, std::stoi(ctx->DECIMAL_LITERAL()->toString()));
    } else if (ctx->LDC()) {
        auto str = ctx->STRING_LITERAL()->toString();
        size_t pos = m_vm.addStringConstant(ObjString::from(str.substr(1, str.size() - 2)));
        return Instruction(OpCode::LDC, Value(pos, Type::REF));
    } else if (ctx->RSTORE()) {
        return Instruction(OpCode::rSTORE,std::stol(ctx->DECIMAL_LITERAL()->getText()));
    }
    UNREACHABLE();
}

antlrcpp::Any VisitorImpl::visitCall(GrammarParser::CallContext *ctx) {
    auto called = ctx->IDENTIFIER();

    size_t posCn = m_vm.addStringConstant(ObjString::from(called[0]->toString()));
    size_t posCm = m_vm.addStringConstant(ObjString::from(called[1]->toString()));
    return Instruction(OpCode::CALLSTATIC, Value(posCn, Type::REF), Value(posCm, Type::REF));
}

antlrcpp::Any VisitorImpl::visitIfBlock(GrammarParser::IfBlockContext *ctx) {
    return visitInstructionsDecl(ctx->instructionsDecl());
}

antlrcpp::Any VisitorImpl::visitElseBlock(GrammarParser::ElseBlockContext *ctx) {
    return visitInstructionsDecl(ctx->instructionsDecl());
}
