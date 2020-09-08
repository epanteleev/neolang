#pragma once

#include "OpCode.h"
#include "Value.h"

struct Instruction {
    explicit Instruction(OpCode code, Value val) :
            opCode(code),
            val(val) {}

    explicit Instruction(OpCode code) :
            opCode(code),
            val(Value()) {}

    OpCode opCode;
    Value val;
};