#pragma once

#include "OpCode.h"
#include "Value.h"

struct Instruction {
    explicit Instruction(OpCode code, Value val) :
            m_opCode(code),
            m_val(val) {}

    explicit Instruction(OpCode code) :
            m_opCode(code),
            m_val(Value()) {}

    inline OpCode code() const noexcept {
        return m_opCode;
    }
    inline Value val() const noexcept {
        return m_val;
    }

private:
    OpCode m_opCode;
    Value m_val;
};