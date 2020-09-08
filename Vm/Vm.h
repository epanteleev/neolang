#pragma once
#include <stack>
#include <vector>
#include <array>
#include "Value.h"
#include "ApiStack.h"

class Instruction;

class Vm {
public:
    Vm() = default;

    Vm(std::vector<Instruction> inst):
        m_insts(std::move(inst))
    {}
    ~Vm() = default;

    inline ApiStack& stack() noexcept {
        return m_apiStack;
    }

    Instruction currentInst() const;

    inline bool hasNext() const noexcept {
        return ip != m_insts.size();
    }

    inline void next() noexcept { ip++; }

    inline void store(Value val, size_t idx) noexcept {
        m_local[idx] = val;
    }

    void trace();
private:
    /// Virtual stack of virtual machine.
    ApiStack m_apiStack;
    ///
    std::vector<Instruction> m_insts;
    std::array<Value, 4> m_local;
    size_t ip{};
};
