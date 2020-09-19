#pragma once

#include <vector>

#include "Value.h"

enum class OpCode : uint8_t {
    iADD,
    iSUB,
    iMUL,
    iDIV,
    iPUSH,
    iSTORE,
    iLOAD,
    fADD,
    fSUB,
    fMULT,
    fDIV,
    CALLSTATIC,
    INVOKE,
    NEW,
    RET
};

constexpr const char *iADD = "iADD";
constexpr const char *iSUB = "iSUB";
constexpr const char *iMUL = "iMUL";
constexpr const char *iDIV = "iDIV";
constexpr const char *iPUSH = "iPUSH";
constexpr const char *iSTORE = "iSTORE";
constexpr const char *fADD = "fADD";
constexpr const char *fSUB = "fSUB";
constexpr const char *fMUL = "fMUL";
constexpr const char *CALLSTATIC = "CALLSTATIC";
constexpr const char *RET = "RET";
constexpr const char *iLOAD = "iLOAD";

struct Instruction {
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

using InstList = std::vector<Instruction>;