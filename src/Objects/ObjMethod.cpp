#include "Objects/ObjMethod.h"
#include "Vm/Vm.h"

VmResult ObjMethod::apply(Environment &env) noexcept {
    size_t sp = env.stack().size();
    env.callStack().enter(*this, sp);
    return VmResult::SUCCESS;
}