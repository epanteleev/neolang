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