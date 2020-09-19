#include "Objects/ObjMethod.h"
#include "Vm/Vm.h"

VmResult ObjMethod::apply(Vm &vm) noexcept {
    size_t sp = vm.stack().size();
    vm.callStack().push(Frame(*this, sp));
    return VmResult::SUCCESS;
}