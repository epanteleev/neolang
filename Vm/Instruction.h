#pragma once

#include "OpCode.h"
#include "Value.h"

struct Instruction {
    explicit Instruction(OpCode code, Value val0, Value val1) :
            m_opCode(code),
            m_arg0(val0),
            m_arg1(val1) {}

    explicit Instruction(OpCode code, Value val) :
            m_opCode(code),
            m_arg0(val) {}

    explicit Instruction(OpCode code) :
            m_opCode(code),
            m_arg0(Value()) {}

    inline OpCode code() const noexcept {
        return m_opCode;
    }

    inline Value arg0() const noexcept {
        return m_arg0;
    }

    inline Value arg1() const noexcept {
        return m_arg1;
    }

private:
    OpCode m_opCode;
    Value m_arg0;
    Value m_arg1;
};

using InstList = std::vector<Instruction>;