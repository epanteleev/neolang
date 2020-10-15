#pragma once
#include <limits>

#include "Objects/ObjFrwd.h"
#include "Vm/Type.h"

class Value {
public:
    constexpr explicit Value() :
            m_value(std::numeric_limits<uint64_t>::min()),
            m_type(Type::UNDEFINED) {}

    constexpr explicit Value(uint64_t value, Type type) :
            m_value(value),
            m_type(type) {}

    constexpr explicit Value(int val) :
            m_value(val),
            m_type(Type::INT32) {}

    constexpr explicit Value(float val) :
            m_value(val),
            m_type(Type::FLOAT32) {}

    constexpr explicit Value(double val) :
            m_value(val),
            m_type(Type::FLOAT64) {}

    constexpr explicit Value(uintptr_t ref) :
            m_value(ref),
            m_type(Type::REF) {}

    [[nodiscard]]
    constexpr Type type() const noexcept { return m_type; }

    [[nodiscard]]
    constexpr uint64_t value() const noexcept { return m_value; }

public: // Conversions.
    [[nodiscard]]
    inline constexpr int32_t toInt32() const noexcept {
        ASSERT(m_type == Type::INT32, "Invalid cast.");
        return (int32_t) (m_value);
    }

    [[nodiscard]]
    inline constexpr uint64_t toUint64() const noexcept {
        ASSERT(m_type == Type::UINT64, "Invalid cast.");
        return (uint64_t) (m_value);
    }

    [[nodiscard]]
    inline constexpr float toFloat32() const noexcept {
        ASSERT(m_type == Type::FLOAT32, "Invalid cast.");
        return (float) (m_value);
    }

    [[nodiscard]]
    inline constexpr double toFloat64() const noexcept {
        ASSERT(m_type == Type::FLOAT64, "Invalid cast.");
        return (double) (m_value);
    }

    [[nodiscard]]
    inline constexpr void *toPtr() const noexcept {
        ASSERT(m_type == Type::REF, "Invalid cast to reference.");
        return reinterpret_cast<void *>(m_value);
    }

public:
    inline constexpr bool operator==(const Value &value) const noexcept {
        //Bug: Compare floating point value.
        return m_type == value.m_type && m_value == value.m_value;
    }

    inline constexpr bool operator<(const Value &value) const noexcept {
        return (m_type != Type::REF) && (m_type != Type::UNDEFINED) && m_value < value.m_value;
    }

    inline constexpr bool operator>=(const Value &value) const noexcept {
        return !(*this < value);
    }

    inline constexpr bool operator<(uint64_t value) const noexcept {
        return (m_type == Type::INT32) && m_value < value;
    }

private:
    uint64_t m_value;
    Type m_type;
};