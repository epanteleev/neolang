#pragma once

#include <stack>
#include "Vm/Frame.h"

class CallStack final {
public:
    CallStack() = default;

    CallStack(CallStack &) = delete;

    ~CallStack() = default;

    CallStack operator=(CallStack &) = delete;

public:
    inline Frame leave() {
        ASSERT(!m_stack.empty(), "CallStack is empty.");
        auto frame = m_stack.top();
        m_stack.pop();
        return frame;
    }

    inline void enter(ObjMethodBase &method) {
        m_stack.emplace(method, 0);
    }

    inline void enter(ObjMethodBase &method, std::size_t sp) {
        m_stack.emplace(method, sp);
    }

    inline Frame &frame() {
        return m_stack.top();
    }

    [[nodiscard]]
    inline bool empty() const {
        return m_stack.empty();
    }

    void stacktrace();

private:
    std::stack<Frame> m_stack;
};
