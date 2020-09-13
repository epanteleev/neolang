#include "Modules/StringModule.h"

#include "Vm/Vm.h"

void StringModule::constr(Vm &vm) noexcept {
    printf("String::<new>\n");
    auto obj = new StringInstance();
    obj->rtti = static_cast<StringModule*>(vm.nativeModules().findModule("String"));
    vm.stack().push(Value((uintptr_t)obj));
}

void StringModule::printType(Vm &vm) noexcept {
    Value val = vm.stack().top();
    printf("Called %s\n", ((StringInstance*)val.value())->rtti->moduleName().data());
}
