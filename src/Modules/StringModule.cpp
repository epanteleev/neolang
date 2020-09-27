#include "Modules/StringModule.h"

#include "Vm/Vm.h"

VmResult StringModule::printType(Vm &vm) noexcept {
    Value val = vm.stack().top();
    printf("Called %s\n", ((StringInstance*)val.value())->rtti->moduleName().cstr());
    return VmResult::SUCCESS;
}

VmResult StringModule::concat(Vm &vm) noexcept {
    ObjStringViewer viewer0(vm.load(0));
    ObjStringViewer viewer1(vm.load(1));
    vm.stack().push((viewer0 + viewer1).toValue());
    return VmResult::SUCCESS;
}
