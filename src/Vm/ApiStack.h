#pragma once

#include <array>
#include "Vm/Value.h"

class ApiStack final {
private:
    static constexpr size_t MAX_STACK_SIZE = 64;

public:
    ApiStack() = default;

    ~ApiStack() = default;

public:
    [[nodiscard]]
    inline size_t size() const noexcept {
        return m_sp;
    }

    inline void drop(size_t sp) noexcept {
        m_sp = sp;
    }

    inline Value pop() noexcept {
        ASSERT(m_sp != 0, "ApiStack is empty.");
        return m_stack[--m_sp];
    }

    [[nodiscard]]
    inline Value top() const noexcept {
        return m_stack[m_sp - 1];
    }

    [[nodiscard]]
    inline bool empty() const noexcept {
        return m_sp == 0;
    }

    [[nodiscard]]
    inline bool nonEmpty() const noexcept {
        return !empty();
    }

    inline void push(Value value) noexcept {
        ASSERT(m_sp + 1 != MAX_STACK_SIZE, "ApiStack is full.");
        m_stack[m_sp] = value;
        m_sp++;
    }

    inline Value* begin() noexcept {
        return &m_stack[0];
    }

    inline Value* end() noexcept {
        return &m_stack[m_sp];
    }

private:
    std::array<Value, MAX_STACK_SIZE> m_stack;
    size_t m_sp{};
};