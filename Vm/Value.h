#pragma once

#include <cstdint>
#include <climits>

#include "ObjFrwd.h"
#include "TypeCheck.h"

class Value {
public:
    explicit Value() :
            m_value(INT_MIN),
            m_type(Type::UNDEFINED) {}

    explicit Value(uint64_t value, Type type) :
            m_value(value),
            m_type(type) {}

    explicit Value(int val) :
            m_value(val),
            m_type(Type::INT32) {}

    explicit Value(float val) :
            m_value(val),
            m_type(Type::FLOAT32) {}

    explicit Value(double val) :
            m_value(val),
            m_type(Type::FLOAT64) {}

    Value(uintptr_t ref) :
            m_value(ref),
            m_type(Type::REF) {}

    constexpr Type type() const noexcept { return m_type; }

    constexpr uint64_t value() const noexcept { return m_value; }

public: // Conversions.
    inline constexpr int toInt32() const noexcept {
        ASSERT(m_type == Type::INT32, "Invalid cast.");
        return (int) (m_value);
    }

    inline constexpr float toFloat32() const noexcept {
        ASSERT(m_type == Type::FLOAT32, "Invalid cast.");
        return (float) (m_value);
    }

    inline Object *toObject() const noexcept {
        ASSERT(m_type == Type::REF, "Invalid cast to reference.");
        return (Object *) ((uintptr_t) m_value);
    }

public:
    inline bool operator==(const Value &value) const noexcept {
        return m_type == value.m_type && m_value == value.m_value;
    }

    inline bool operator<(const Value &value) const noexcept {
        return m_type < value.m_type && m_value < value.m_value;
    }

    inline bool operator>=(const Value &value) const noexcept {
        return !(*this < value);
    }

    inline bool operator<(uint64_t value) const noexcept {
        return m_type == Type::INT32 && m_value < value;
    }


private:

    uint64_t m_value;
    Type m_type;
};