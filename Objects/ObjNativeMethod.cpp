#include "Objects/ObjNativeMethod.h"
#include "Vm/Vm.h"

VmResult ObjNativeMethod::apply(Vm &vm) noexcept {
    vm.callStack().push(Frame(*this));
    const auto res = m_func(vm);
    vm.callStack().pop();
    return res;
}
