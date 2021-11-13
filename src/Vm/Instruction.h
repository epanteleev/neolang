#pragma once

#include <vector>
#include <list>
#include <sstream>
#include <Objects/ObjString.h>

#include "Vm/Value.h"
#include "Vm/OpCode.h"

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

    Instruction &operator=(const Instruction &inst) noexcept = delete;

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

public:
    [[nodiscard]]
    std::string toString() const {
        std::stringstream stream;
        stream << opCodeToString(m_opCode);
        return stream.str();
    }

public:
    inline static Instruction iPUSH(const std::string &integer) {
        return Instruction(OpCode::iPUSH, std::stoi(integer));
    }

    inline static Instruction iLOAD(const std::string &cell) {
        return Instruction(OpCode::iLOAD, std::stoi(cell));
    }

    inline static Instruction iSTORE(const std::string &cell) {
        return Instruction(OpCode::iSTORE, std::stoi(cell));
    }

    inline static Instruction fPUSH(const std::string &floatValue) {
        return Instruction(OpCode::fPUSH, std::stof(floatValue));
    }

    inline static Instruction fSTORE(const std::string &cell) {
        return Instruction(OpCode::fSTORE, std::stoi(cell));
    }

    inline static Instruction fLOAD(const std::string &cell) {
        return Instruction(OpCode::fLOAD, std::stoi(cell));
    }

    static Instruction LDC(const std::string &stringLiteral);

    inline static Instruction rSTORE(const std::string &cell) {
        return Instruction(OpCode::rSTORE, std::stoi(cell));
    }

    inline static Instruction rLOAD(const std::string &cell) {
        return Instruction(OpCode::rLOAD, std::stoi(cell));
    }

    static Instruction PUTFIELD(const std::string &fieldName);

    static Instruction GETFIELD(const std::string &fieldName);

    static Instruction NEW(const std::string &className);

    static Instruction CALL(const std::string &module, const std::string &method);

private:
    OpCode m_opCode;
    Value m_arg0;
    Value m_arg1;
};

using InstructionList = std::vector<Instruction>;

using StreamInstruction = std::list<Instruction>;