#include "Objects/ObjMethod.h"
#include "Vm/Vm.h"

VmResult ObjMethod::apply(Vm &vm) noexcept {
    vm.callStack().push(Frame(*this));
    return VmResult::SUCCESS;
}