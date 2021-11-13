#include "Vm/Frame.h"
#include "Objects/Method/ObjMethod.h"

Instruction Frame::inst() noexcept {
    return m_method.asMethod().instList()[static_cast<size_t>(m_ip)];
}

bool Frame::hasNext() const noexcept {
    return static_cast<size_t>(m_ip) < m_method.asMethod().instList().size();
}
