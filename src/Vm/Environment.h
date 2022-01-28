#pragma once

#include "Vm/Instruction.h"
#include "Vm/CallStack.h"
#include "Vm/ApiStack.h"
#include "Vm/Locals.h"
#include "Vm/Value.h"
#include "Vm/Frame.h"

class Environment final {
public:
    Environment(ApiStack &apiStack, Locals &locals, CallStack &callStack) :
            m_apiStack(apiStack),
            m_local(locals),
            m_callStack(callStack)
            {}

    Environment(Vm &) = delete;

    ~Environment() = default;

    Environment operator=(Environment &) = delete;

public:
    forceinline ApiStack &stack() noexcept {
        return m_apiStack;
    }

    forceinline Locals &locals() noexcept {
        return m_local;
    }

    forceinline CallStack &callStack() noexcept {
        return m_callStack;
    }

private:
    ApiStack &m_apiStack;
    Locals &m_local;
    CallStack &m_callStack;
};
