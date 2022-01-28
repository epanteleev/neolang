#pragma once
#include <limits>
#include <cinttypes>
#include "Vm/Common.h"
#include "Objects/ObjFrwd.h"

/**
 * Represent value in virtual machine.
 * @author minium2
 */
class Value final {
public:
    using value_type = uint64_t;

public:
    enum class Type : uint8_t {
        UNDEFINED,
        INT32,
        UINT64,
        FLOAT32,
        FLOAT64,
        BOOL,
        REF
    };

    static constexpr const char *U64 = "u64";
    static constexpr const char *I32 = "i32";
    static constexpr const char *REF = "ref";
    static constexpr const char *F32 = "f32";
    static constexpr const char *F64 = "f64";
    static constexpr const char *UD  = "ud";
    static constexpr const char *BOOL  = "bool";

public:
    constexpr explicit Value() :
            m_value(std::numeric_limits<uint64_t>::max()),
            m_type(Type::UNDEFINED) {}

    constexpr explicit Value(uint64_t value, Type type) :
            m_value(value),
            m_type(type) {}

    constexpr Value(int val) :
            m_value(val),
            m_type(Type::INT32) {}

    constexpr Value(float val) :
            m_value(val),
            m_type(Type::FLOAT32) {}

    constexpr Value(double val) :
            m_value(val),
            m_type(Type::FLOAT64) {}

    constexpr Value(long ref) :
            m_value(ref),
            m_type(Type::UINT64) {}

    [[nodiscard]]
    constexpr Type type() const noexcept { return m_type; }

    [[nodiscard]]
    constexpr value_type value() const noexcept { return m_value; }

public: // Conversions.
    [[nodiscard]]
    inline constexpr int32_t toInt32() const noexcept {
        ASSERT(m_type == Type::INT32, "Invalid cast.");
        return (int32_t) (m_value);
    }

    [[nodiscard]]
    inline constexpr int32_t toBool() const noexcept {
        ASSERT(m_type == Type::BOOL, "Invalid cast.");
        return (bool) (m_value);
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
    inline void *toPtr() const noexcept {
        ASSERT(m_type == Type::REF, "Invalid cast to reference.");
        return reinterpret_cast<void *>(m_value);
    }

public:
    inline constexpr bool operator==(const Value &value) const noexcept {
        //Todo(bug): Compare floating point value.
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

    [[nodiscard]]
    constexpr const char * typeToString() const noexcept {
        switch (m_type) {
            case Type::INT32:   return I32;
            case Type::REF:     return REF;
            case Type::FLOAT32: return F32;
            case Type::UINT64:  return U64;
            case Type::BOOL:    return BOOL;
            default:            return UD;
        }
    }

public:
    static Type stringToType(const char *str) noexcept;

private:
    value_type m_value;
    Type m_type;
};