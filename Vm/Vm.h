#pragma once

#include <stack>
#include <vector>
#include <array>
#include <map>

#include "Value.h"
#include "ApiStack.h"
#include "ObjMethod.h"
#include "Instruction.h"
#include "SymbolTable.h"
#include "ObjModule.h"

class Vm {
public:
    Vm() = default;

    explicit Vm(std::vector<Instruction> inst, SymbolTable symTable) :
            m_insts(std::move(inst)),
            m_symTable(std::move(symTable)) {}

    ~Vm() = default;

    inline ApiStack &stack() noexcept {
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

    inline NativeFunc findFunc(const std::string &name) noexcept {
        return m_symTable[name];
    }

    void trace();

private:
    /// Virtual stack of virtual machine.
    ApiStack m_apiStack;
    ///
    std::vector<Instruction> m_insts;
    std::array<Value, 4> m_local;
    SymbolTable m_symTable;
    size_t ip{};

    std::list<std::unique_ptr<ObjModule>> m_modules;
};
