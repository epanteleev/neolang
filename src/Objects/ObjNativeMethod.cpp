#include "Objects/ObjNativeMethod.h"
#include "Vm/Vm.h"

VmResult ObjNativeMethod::apply(Vm &vm) noexcept {
    size_t sp = vm.stack().size();
    vm.callStack().push(Frame(*this, sp));
    const auto res = m_func(vm);
    vm.callStack().pop();
    return res;
}
