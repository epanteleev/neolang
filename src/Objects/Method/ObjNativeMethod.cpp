#include "ObjNativeMethod.h"
#include "Vm/Vm.h"

VmResult ObjNativeMethod::apply(Environment &env) noexcept {
    size_t sp = env.stack().size();
    env.callStack().enter(*this, sp);
    const auto res = m_func(env);
    env.callStack().leave();
    return res;
}
