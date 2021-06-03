#include "Vm/Frame.h"
#include "Objects/ObjMethod.h"

Instruction Frame::inst() noexcept {
    ASSERT(!m_method.isNative(), "Try executed native method.");
    return m_method.asMethod().instList()[static_cast<size_t>(m_ip)];
}

bool Frame::hasNext() const noexcept {
    ASSERT(!m_method.isNative(), "Try executed native method.");
    return static_cast<size_t>(m_ip) < m_method.asMethod().instList().size();
}
