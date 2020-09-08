#pragma once
#include <cstdint>

enum class OpCode: uint8_t {
    iADD,
    iPUSH,
    iSTORE,
    CALL
};

