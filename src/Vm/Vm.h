#pragma once

#include <stack>
#include <vector>
#include <array>

#include "Objects/ObjNativeModule.h"
#include "Objects/ModuleBuffer.h"
#include "Objects/ObjMethod.h"
#include "Objects/ObjModule.h"

#include "Vm/Allocator/Allocator.h"
#include "Vm/Instruction.h"
#include "Vm/ApiStack.h"
#include "Vm/Value.h"
#include "Vm/Frame.h"

enum class VmResult {
    SUCCESS,
    TERMINATE,
    ZERO_DIVISION
};
static constexpr size_t MAX_LOCAL_VARS = 4;
using Locals = std::array<Value, MAX_LOCAL_VARS>;

class Vm {
public:
    Vm() = default;

    Vm(Vm &) = delete;

    ~Vm() = default;

public:

    inline void addModule(std::unique_ptr<ObjModule> &module) noexcept {
        m_modules.addModule(module);
    }

    inline void addModule(std::unique_ptr<ObjNativeModule> &module) noexcept {
        m_modules.addModule(module);
    }

    inline ApiStack &stack() noexcept {
        return m_apiStack;
    }

    inline Locals &locals() noexcept {
        return m_local;
    }

    inline Frame &frame() noexcept {
        return m_callStack.top();
    }

    inline CallStack &callStack() noexcept {
        return m_callStack;
    }

    inline ModuleBuffer &modules() noexcept {
        return m_modules;
    }

public:
    inline void store(Value val, size_t idx) noexcept {
        ASSERT(idx < MAX_LOCAL_VARS, "Invalid variable index.");
        m_local[idx] = val;
    }

    [[nodiscard]]
    inline Value load(size_t idx) const noexcept {
        ASSERT(idx < MAX_LOCAL_VARS, "Invalid local variables index.");
        return m_local[idx];
    }

    inline void leave() noexcept {
        ASSERT(!m_callStack.empty(), "CallStack is empty.");
        const auto frame = m_callStack.top();
        m_callStack.pop();
        ASSERT(m_apiStack.size() == frame.savedSp(), "Frame non empty.");
    }

    void trace();

    void vmError(const ObjString &message) noexcept;

private:
    /** Virtual stack of virtual machine. */
    ApiStack m_apiStack;
    Locals m_local;

    CallStack m_callStack;
    ModuleBuffer m_modules;
};
