#pragma once

#include <stack>

#include "Objects/Method/ObjMethodBase.h"
#include "Vm/Instruction.h"

class Frame final {
public:
    explicit Frame(ObjMethodBase &method, std::size_t sp) :
            m_method(method),
            m_ip(0),
            m_sp(sp) {}

    Instruction inst() noexcept;

    [[nodiscard]]
    bool hasNext() const noexcept;

    inline void next() noexcept {
        m_ip++;
    }

    inline void gotoInst(std::size_t ip) noexcept {
        m_ip = ip;
    }

    [[nodiscard]]
    inline ObjMethodBase &method() const noexcept {
        return m_method;
    }

    [[nodiscard]]
    inline std::size_t savedSp() const noexcept {
        return m_sp;
    }

private:
    ObjMethodBase &m_method;
    std::size_t m_ip;
    const std::size_t m_sp;
};