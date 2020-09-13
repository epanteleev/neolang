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
    static bool apply(Vm &vm) noexcept;
};

class iSub : public Interpret {
public:
    static bool apply(Vm &vm) noexcept;
};

class iMult : public Interpret {
public:
    static bool apply(Vm &vm) noexcept;
};

class iPush : public Interpret {
public:
    static bool apply(Vm &vm) noexcept;
};

class iStore : public Interpret {
public:
    static bool apply(Vm &vm) noexcept;
};

class CallStatic : public Interpret {
public:
    static bool apply(Vm &vm) noexcept;
};

class Ret : public Interpret {
public:
    static bool apply(Vm &vm) noexcept;
};

class Invoke : public Interpret {
public:
    static bool apply(Vm& vm) noexcept;
};

class New : public Interpret {
public:
    static bool apply(Vm& vm) noexcept;
};