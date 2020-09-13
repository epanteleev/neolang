#pragma once

#include <vector>
#include <stack>

#include "Objects/ObjMethod.h"

class Frame {
public:
    explicit Frame(ObjMethod& method) :
            m_method(method),
            m_ip(0) {}

    inline Instruction inst() const noexcept {
        return m_method.insts()[m_ip];
    }

    inline bool hasNext() const noexcept {
        return m_ip != m_method.insts().size();
    }

    inline void next() noexcept {
        m_ip++;
    }

    inline ObjMethod& method() noexcept {
        return m_method;
    }

private:
    ObjMethod &m_method;
    size_t m_ip;
};

using CallStack = std::stack<Frame>;