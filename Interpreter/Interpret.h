#pragma once

#include "Vm/ApiStack.h"
#include "Vm/Value.h"
#include "Vm/TypeCheck.h"
#include "Vm/Vm.h"
#include "Vm/Instruction.h"
#include "Vm/Common.h"

class Interpret {
public:
    static bool apply(const std::string& moduleName, Vm &vm);
};

class iAdd : public Interpret {
public:
    static bool apply(Vm &vm) noexcept {
        const auto a = vm.stack().pop();
        const auto b = vm.stack().pop();
        const auto result = a.toInt32() + b.toInt32();
        vm.stack().push(Value(result));
        return true;
    }
};

class iSub : public Interpret {
public:
    static bool apply(Vm &vm) noexcept {
        const auto a = vm.stack().pop();
        const auto b = vm.stack().pop();
        const auto result = a.toInt32() - b.toInt32();
        vm.stack().push(Value(result));
        return true;
    }
};

class iMult : public Interpret {
public:
    static bool apply(Vm &vm) noexcept {
        const auto a = vm.stack().pop();
        const auto b = vm.stack().pop();
        const auto result = a.toInt32() * b.toInt32();
        vm.stack().push(Value(result));
        return true;
    }
};

class iPush : public Interpret {
public:
    static bool apply(Vm &vm) noexcept {
        const auto inst = vm.frame().inst();
        vm.stack().push(inst.arg0());
        return true;
    }
};

class iStore : public Interpret {
public:
    static bool apply(Vm &vm) noexcept {
        const auto instruction = vm.frame().inst();
        const auto variable = instruction.arg0();
        TRACE(vm, vm.stack().nonEmpty(), "ApiStack is empty.");
        TRACE(vm, variable < 4, "Invalid variable index.");
        const auto a = vm.stack().pop();
        if (a.type() == Type::INT32) {
            vm.store(a, variable.value());
        } else {
            TRACE(vm, false, "Incomparable type.");
        }
        return true;
    }
};

class CallStatic : public Interpret {
public:
    static bool apply(Vm &vm) noexcept;
};

class Ret : public Interpret {
public:
    static bool apply(Vm &vm) noexcept {
        TRACE(vm, !vm.callStack().empty(), "CallStack is empty.");
        vm.callStack().pop();
        return true;
    }
};