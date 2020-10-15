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

constexpr const char *U64 = "u64";
constexpr const char *I32 = "i32";
constexpr const char *REF = "ref";
constexpr const char *F32 = "f32";
constexpr const char *UD  = "ud";

inline constexpr const char *typeToString(Type type) noexcept {
    switch (type) {
        case Type::INT32:   return I32;
        case Type::REF:     return REF;
        case Type::FLOAT32: return F32;
        case Type::UINT64:  return U64;
        default:            return UD;
    }
}