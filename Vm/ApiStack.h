#pragma once

#include <stack>
#include "Value.h"

class ApiStack final {
public:
    ApiStack() = default;
    ~ApiStack() = default;

    inline Value pop() noexcept {
        const auto elem = m_stack.top();
        m_stack.pop();
        return elem;
    }

    inline Value top() const noexcept {
        return m_stack.top();
    }

    inline bool empty() const noexcept {
        return m_stack.empty();
    }

    inline bool nonEmpty() const noexcept {
        return !empty();
    }

    inline void push(Value value) {
        m_stack.push(value);
    }
private:
    std::stack<Value> m_stack;
};