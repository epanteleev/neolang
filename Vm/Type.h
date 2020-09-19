#pragma once

#include <cstdint>
#include <cassert>
#include "Common.h"

enum class Type : uint8_t {
    UNDEFINED,
    INT32,
    UINT64,
    FLOAT32,
    FLOAT64,
    REF
};