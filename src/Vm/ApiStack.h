#pragma once

#include <array>
#include "Vm/Value.h"

/**
 * Represent machine stack in virtual machine.
 * @author minium2
 */
class ApiStack final {
private:
    static constexpr size_t MAX_STACK_SIZE = 256;

public:
    ApiStack() = default;

    ApiStack(ApiStack &) = delete;

    ~ApiStack() = default;

    ApiStack operator=(ApiStack &) = delete;

public:
    [[nodiscard]]
    inline size_t size() const noexcept {
        return m_sp;
    }

    [[nodiscard]]
    inline Value pop() noexcept {
        ASSERT(m_sp != 0, "ApiStack is empty.");
        return m_stack[--m_sp];
    }

    [[nodiscard]]
    inline Value top() noexcept {
        return m_stack[m_sp - 1];
    }

    [[nodiscard]]
    constexpr inline bool empty() const noexcept {
        return m_sp == 0;
    }

    [[nodiscard]]
    constexpr inline bool nonEmpty() const noexcept {
        return !empty();
    }

    inline void push(Value value) noexcept {
        ASSERT(m_sp + 1 != MAX_STACK_SIZE, "ApiStack is full.");
        m_stack[m_sp] = value;
        m_sp++;
    }

    template<typename... Arg>
    void emplace(Arg&&... value) noexcept {
        ASSERT(m_sp + 1 != MAX_STACK_SIZE, "ApiStack is full.");
        m_stack[m_sp] = Value(std::forward<Arg>(value)...); //Todo maybe std::launder???
        m_sp++;
    }

    constexpr inline Value* begin() noexcept {
        return &m_stack[0];
    }

    constexpr inline Value* end() noexcept {
        return &m_stack[m_sp];
    }

private:
    std::array<Value, MAX_STACK_SIZE> m_stack;
    size_t m_sp{};
};