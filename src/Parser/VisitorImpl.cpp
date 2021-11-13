#include <generated/GrammarParser.h>
#include <generated/GrammarBaseVisitor.h>
#include "Parser/VisitorImpl.h"

antlrcpp::Any VisitorImpl::visitCompilationUnit(GrammarParser::CompilationUnitContext *ctx) {
    return visitClassDeclaration(ctx->classDeclaration());
}

antlrcpp::Any VisitorImpl::visitClassDeclaration(GrammarParser::ClassDeclarationContext *ctx) {

    auto moduleName = ObjString::from(ctx->IDENTIFIER()->toString());
    auto module = ObjModule::make(std::move(moduleName));

    std::size_t offset = 0;
    for (auto &i: ctx->field()) {
        auto fieldName = i->IDENTIFIER().back()->toString();
        auto pos = Vm::strings().push(fieldName.c_str());

        auto type = Value::stringToType(i->IDENTIFIER().front()->toString().c_str());
        module->addField(pos, offset, type);
        offset += 1;
    }

    for (auto &i: ctx->methodDeclaration()) {
        module->addMethod(visitMethodDeclarationOverride(i));
    }
    Vm::registerModule(std::move(module));
    return antlrcpp::Any();
}

std::unique_ptr<ObjMethod> VisitorImpl::visitMethodDeclarationOverride(GrammarParser::MethodDeclarationContext *ctx) {
    std::string str = ctx->IDENTIFIER()->toString();
    auto methodName = ObjString::from(str);

    StreamInstruction list = visitInstructionsDecl(ctx->instructionsDecl()).as<StreamInstruction>();
    InstructionList v{std::make_move_iterator(std::begin(list)), std::make_move_iterator(std::end(list))}; //Todo
    return ObjMethod::make(std::move(methodName), std::move(v));
}

antlrcpp::Any VisitorImpl::visitInstructionsDecl(GrammarParser::InstructionsDeclContext *ctx) {
    StreamInstruction list;
    if (ctx == nullptr) {
        return list;
    }
    if (ctx->instruction() != nullptr) {
        list.push_back(visitInstruction(ctx->instruction()).as<Instruction>());
    } else if (ctx->ifBlock()) {
        StreamInstruction ifBlock = visitIfBlock(ctx->ifBlock()).as<StreamInstruction>();

        if (ctx->elseBlock()) {
            StreamInstruction elseBlock = visitElseBlock(ctx->elseBlock()).as<StreamInstruction>();

            list.emplace_back(OpCode::JUMP, Value(ifBlock.size() + 1, Value::Type::REF));
            std::move(ifBlock.begin(), ifBlock.end(), std::back_inserter(list));

            list.emplace_back(OpCode::GOTO, Value(elseBlock.size(), Value::Type::REF));

            std::move(elseBlock.begin(), elseBlock.end(), std::back_inserter(list));

        } else {
            list.emplace_back(OpCode::JUMP, Value(ifBlock.size(), Value::Type::REF));
            std::move(ifBlock.begin(), ifBlock.end(), std::back_inserter(list));
        }
    }

    StreamInstruction nextList = VisitorImpl::visitInstructionsDecl(ctx->instructionsDecl()).as<StreamInstruction>();
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
    } else if (ctx->RRET()) {
        return Instruction(OpCode::RRET);
    } else if (ctx->CMPEQ()) {
        return Instruction(OpCode::CMPEQ);
    } else if (ctx->AND()) {
        return Instruction(OpCode::AND);
    } else if (ctx->OR()) {
        return Instruction(OpCode::OR);
    } else if (ctx->IRET()) {
        return Instruction(OpCode::iRET);
    } else if (ctx->SWAP()) {
        return Instruction(OpCode::SWAP);
    } else if (ctx->DUP()) {
        return Instruction(OpCode::DUP);
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
        return Instruction::iPUSH(ctx->DECIMAL_LITERAL()->toString());
    } else if (ctx->ILOAD()) {
        return Instruction::iLOAD(ctx->DECIMAL_LITERAL()->toString());
    } else if (ctx->ISTORE()) {
        return Instruction::iSTORE(ctx->DECIMAL_LITERAL()->toString());
    } else if (ctx->FPUSH()) {
        return Instruction::fPUSH(ctx->FLOAT_LITERAL()->toString());
    } else if (ctx->FSTORE()) {
        return Instruction::fSTORE(ctx->DECIMAL_LITERAL()->toString());
    } else if (ctx->FLOAD()) {
        return Instruction::fLOAD(ctx->DECIMAL_LITERAL()->toString());
    } else if (ctx->LDC()) {
        return Instruction::LDC(ctx->STRING_LITERAL()->toString());
    } else if (ctx->RSTORE()) {
        return Instruction::rSTORE(ctx->DECIMAL_LITERAL()->getText());
    } else if (ctx->RLOAD()) {
        return Instruction::rLOAD(ctx->DECIMAL_LITERAL()->getText());
    } else if (ctx->PUTFIELD()) {
        return Instruction::PUTFIELD(ctx->IDENTIFIER()->toString());
    } else if (ctx->GETFIELD()) {
        return Instruction::GETFIELD(ctx->IDENTIFIER()->toString());
    } else if (ctx->NEW()) {
        return Instruction::NEW(ctx->IDENTIFIER()->toString());
    }
    UNREACHABLE();
}

antlrcpp::Any VisitorImpl::visitCall(GrammarParser::CallContext *ctx) {
    auto called = ctx->IDENTIFIER();
    return Instruction::CALL(called[0]->toString(),called[1]->toString());
}

antlrcpp::Any VisitorImpl::visitIfBlock(GrammarParser::IfBlockContext *ctx) {
    return visitInstructionsDecl(ctx->instructionsDecl());
}

antlrcpp::Any VisitorImpl::visitElseBlock(GrammarParser::ElseBlockContext *ctx) {
    return visitInstructionsDecl(ctx->instructionsDecl());
}