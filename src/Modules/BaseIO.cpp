#include "Modules/BaseIO.h"

#include "Vm/Vm.h"
#include <iostream>

VmResult BaseIO::printInt(Vm &vm) noexcept {
    auto value = vm.load(0);
    std::cout << value.toInt32();
    return VmResult::SUCCESS;
}

VmResult BaseIO::printFloat(Vm &vm) noexcept {
    auto value = vm.load(0);
    std::cout << value.toFloat32();
    return VmResult::SUCCESS;
}

VmResult BaseIO::readInt(Vm &vm) noexcept {
    int i = 0;
    std::cin >> i;
    vm.stack().push(Value(i));
    return VmResult::SUCCESS;
}

VmResult BaseIO::readFloat(Vm &vm) noexcept {
    float i = 0;
    std::cin >> i;
    vm.stack().push(Value(i));
    return VmResult::SUCCESS;
}

std::unique_ptr<ObjNativeModule> BaseIO::makeModule() noexcept {
    auto module = std::make_unique<BaseIO>();

    auto method0 = ObjNativeMethod::make(*module, "printInt", printInt);
    module->addMethod(method0);

    auto method1 = ObjNativeMethod::make(*module, "printFloat", printFloat);
    module->addMethod(method1);

    auto method2 = ObjNativeMethod::make(*module, "readInt", readInt);
    module->addMethod(method2);

    auto method3 = ObjNativeMethod::make(*module, "readFloat", readFloat);
    module->addMethod(method3);
    return module;
}
