#pragma once

#include <cstdint>

enum class OpCode : uint8_t {
    iADD,
    iSUB,
    iMULT,
    iDIF,
    iPUSH,
    iSTORE,
    fADD,
    fSUB,
    fMULT,
    fDIF,
    CALL
};

