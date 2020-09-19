#pragma once

#include "Vm/ApiStack.h"
#include "Vm/Value.h"
#include "Vm/Type.h"
#include "Vm/Vm.h"
#include "Vm/Instruction.h"
#include "Vm/Common.h"

class Interpret {
public:
    static VmResult apply(const std::string& moduleName, Vm &vm);
};

#define INTERPRET(opCode)                       \
    class opCode : public Interpret {           \
    public:                                     \
        static VmResult apply(Vm &vm) noexcept; \
    };                                          \

INTERPRET(iAdd)
INTERPRET(iSub)
INTERPRET(iMul)
INTERPRET(iPush)
INTERPRET(iDiv)
INTERPRET(iStore)
INTERPRET(CallStatic)
INTERPRET(Ret)
INTERPRET(Invoke)
INTERPRET(New)
INTERPRET(fAdd)
INTERPRET(fSub)
INTERPRET(fDiv)
INTERPRET(fMult)