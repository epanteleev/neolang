#pragma once

#include <stack>

#include "Objects/ObjMethod.h"

class Frame final {
public:
    explicit Frame(ObjMethodBase &method, size_t sp) :
            m_method(method),
            m_ip(0),
            m_sp(sp) {}

    [[nodiscard]]
    inline Instruction inst() const noexcept {
        ASSERT(!m_method.isNative(), "Try executed native method.");
        return static_cast<ObjMethod &>(m_method).instList()[static_cast<size_t>(m_ip)];
    }

    [[nodiscard]]
    inline bool hasNext() const noexcept {
        ASSERT(!m_method.isNative(), "Try executed native method.");
        ASSERT(m_ip >= 0, "Invalid ip.");
        return static_cast<size_t>(m_ip) < static_cast<ObjMethod &>(m_method).instList().size();
    }

    inline void next() noexcept {
        m_ip++;
    }

    inline void gotoInst(size_t ip) noexcept {
        m_ip = ip;
    }

    [[nodiscard]]
    inline ObjMethodBase &method() const noexcept {
        return m_method;
    }

    [[nodiscard]]
    inline size_t savedSp() const noexcept {
        return m_sp;
    }

    [[nodiscard]]
    inline const ObjModule& currentModule() const noexcept {
        return dynamic_cast<const ObjModule&>(m_method.module());
    }

private:
    ObjMethodBase &m_method;
    int64_t m_ip;
    const size_t m_sp;
};

using CallStack = std::stack<Frame>;