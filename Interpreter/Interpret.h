#pragma once

#include <ApiStack.h>
#include <Value.h>
#include <TypeCheck.h>
#include "Vm.h"
#include "Instruction.h"
#include "Common.h"

class Interpret {
public:
    typedef void (*Actions)(Vm& vm);
public:
    static void apply(Vm& vm);
};

class iAdd: public Interpret {
public:
    static void apply(Vm& vm) {
        const auto a = vm.stack().pop();
        const auto b = vm.stack().pop();
        const auto result = a.toInt32() + b.toInt32();
        vm.stack().push(Value(result));
    }
};

class iPush: public Interpret {
public:
    static void apply(Vm& vm) {
        vm.stack().push(vm.currentInst().val);
    }
};

class iStore: public Interpret {
public:
    static void apply(Vm& vm) noexcept {
        ASSERT(vm.stack().nonEmpty(), "ApiStack is empty.");
        ASSERT(vm.currentInst().val < 4, "Invalid variable index.");
        const auto a = vm.stack().pop();
        if (a.type() == Type::INT32) {
            vm.store(a, vm.currentInst().val.value());
        } else {
            UNREACHABLE();
        }
    }
};