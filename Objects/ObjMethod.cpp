#include "Objects/ObjMethod.h"
#include "Vm/Vm.h"

bool ObjMethod::apply(Vm &vm) noexcept {
    vm.callStack().push(Frame(*this));
    return true;
}