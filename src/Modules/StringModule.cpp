#include "Modules/StringModule.h"

#include "Vm/Vm.h"

VmResult StringModule::newString(Vm &vm) noexcept {
    printf("String::<new>\n");
    auto obj = new StringInstance();
    obj->rtti = static_cast<StringModule*>(vm.modules().findModule("String"));
    vm.stack().push(Value((uintptr_t)obj));
    return VmResult::SUCCESS;
}

VmResult StringModule::printType(Vm &vm) noexcept {
    Value val = vm.stack().top();
    printf("Called %s\n", ((StringInstance*)val.value())->rtti->moduleName().data());
    return VmResult::SUCCESS;
}
