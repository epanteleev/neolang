#include <iostream>
#include <filesystem>
#include "Parser/Parser.h"
#include "Vm/Vm.h"
#include "Reader.h"

static bool parseInsts(ObjModule &module, ObjMethod &method, Reader &reader) noexcept {
    std::string instName = reader.getWord();
    while (!instName.empty()) {
        if (instName == iPUSH) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::iPUSH, Value(i)));
        } else if (instName == iLOAD) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::iLOAD, i));
        } else if (instName == iSTORE) {
            int i = reader.getInt();
            method.addInst(Instruction(OpCode::iSTORE, i));
        } else if (instName == iADD) {
            method.addInst(Instruction(OpCode::iADD));
        } else if (instName == iSUB) {
            method.addInst(Instruction(OpCode::iSUB));
        } else if (instName == iDIV) {
                method.addInst(Instruction(OpCode::iDIV));
        } else if (instName == iMUL) {
            method.addInst(Instruction(OpCode::iMUL));
        } else if (instName == CALLSTATIC) {
            std::string className, methodName;
            reader.part(className)
                .expect(Keyword::COLON)
                .expect(Keyword::COLON)
                .part(methodName);
            if (!reader.success()) {
                return false;
            }
            module.addStringConstant(className);
            module.addStringConstant(methodName);
            size_t size = module.sizeStringPool();
            method.addInst(Instruction(OpCode::CALLSTATIC, Value((int)size - 2), Value((int)size - 1)));
        } else if (instName == RET) {
            method.addInst(Instruction(OpCode::RET));
        } else {
            UNREACHABLE();
        }
        instName = reader.getWord();
    }
    return true;
}

static bool parseMethod(ObjModule &module, Reader &reader) noexcept {
    std::string methodName;
    reader.expect(Keyword::DEF)
        .part(methodName)
        .expect(Keyword::EQ)
        .expect(Keyword::OPEN_BRACE);
    if (reader.error()) {
        return false;
    } else if (reader.noMatch()) {
        return true;
    }

    auto method = ObjMethod::make(module, methodName);
    parseInsts(module, *method, reader);
    module.addMethod(method);

    reader.expect(Keyword::CLOSE_BRACE);
    if (!reader.success()) {
        return false;
    }
    return true;
}

static bool parseModule(Vm &vm, Reader &reader) noexcept {
    std::string className;
    reader.expect(Keyword::CLASS).part(className).expect(Keyword::OPEN_BRACE);
    if (reader.error()) {
        return false;
    } else if (reader.noMatch()) {
        return true;
    }

    auto module = ObjModule::make(className);
    while (!reader.noMatch()) {
        parseMethod(*module, reader);
    }
    reader.expect(Keyword::CLOSE_BRACE);
    if (reader.error()) {
        return false;
    }
    vm.addModule(module);
    return true;
}


bool Parser::parse(Vm& vm, const std::filesystem::path &path) noexcept {
    Reader reader;
    if (!reader.open(path.string())) {
        std::cerr << "File " << path << " wasn't open." << std::endl;
        return false;
    }
    if (!parseModule(vm, reader)) {
        std::cerr << "Parse error." << std::endl;
        return false;
    }
    return true;
}
