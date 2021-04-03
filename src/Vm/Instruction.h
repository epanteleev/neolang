#pragma once

#include <vector>
#include <list>

#include "Vm/Value.h"
#include "Vm/OpCode.h"

struct Instruction {
    Instruction() :
        m_opCode(OpCode::UNDEFINED) {}

    explicit Instruction(OpCode code, Value val0, Value val1) :
            m_opCode(code),
            m_arg0(val0),
            m_arg1(val1) {}

    explicit Instruction(OpCode code, Value val) :
            m_opCode(code),
            m_arg0(val),
            m_arg1(Value()) {}

    explicit Instruction(OpCode code) :
            m_opCode(code),
            m_arg0(Value()),
            m_arg1(Value()) {}

    Instruction& operator=(const Instruction& inst) noexcept = default;

public:
    [[nodiscard]]
    inline OpCode code() const noexcept {
        return m_opCode;
    }

    [[nodiscard]]
    inline Value arg0() const noexcept {
        return m_arg0;
    }

    [[nodiscard]]
    inline Value arg1() const noexcept {
        return m_arg1;
    }

private:
    OpCode m_opCode;
    Value m_arg0;
    Value m_arg1;
};

using InstructionList = std::vector<Instruction>;

using StreamInstruction = std::list<Instruction>;