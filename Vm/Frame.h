#pragma once

#include <vector>
#include <stack>

#include "Objects/ObjMethod.h"

class Frame {
public:
    explicit Frame(ObjMethodBase& method) :
            m_method(method),
            m_ip(0) {}

    [[nodiscard]]
    inline Instruction inst() const noexcept {
        ASSERT(!m_method.isNative(), "Try executed native method.");
        return static_cast<ObjMethod&>(m_method).insts()[m_ip];
    }

    [[nodiscard]]
    inline bool hasNext() const noexcept {
        ASSERT(!m_method.isNative(), "Try executed native method.");
        return m_ip != static_cast<ObjMethod&>(m_method).insts().size();
    }

    inline void next() noexcept {
        m_ip++;
    }

    inline ObjMethodBase& method() noexcept {
        return m_method;
    }

private:
    ObjMethodBase &m_method;
    size_t m_ip;
};

using CallStack = std::stack<Frame>;