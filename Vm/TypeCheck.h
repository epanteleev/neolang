#pragma once
#include <cstdint>
#include <cassert>
#include "Common.h"
enum class Type: uint8_t {
    INT32,
    UINT64,
    FLOAT32,
    FLOAT64,
    REF,
    UNDEFINED
};

class TypeCheck {
public:
    static Type interference(Type a, Type b) {
        if(a == b) {
            return a;
        } else {
            UNREACHABLE();
        }
    }
};
