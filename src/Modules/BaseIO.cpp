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

VmResult BaseIO::printString(Vm &vm) noexcept {
    auto value = vm.load(0);
    ObjStringViewer ptr(value);
    std::cout << ptr;
    return VmResult::SUCCESS;
}

std::unique_ptr<ObjNativeModule> BaseIO::makeModule() noexcept {
    auto module = std::make_unique<BaseIO>();

    auto method0 = ObjNativeMethod::make("printInt", printInt);
    module->addMethod(std::move(method0));

    auto method1 = ObjNativeMethod::make("printFloat", printFloat);
    module->addMethod(std::move(method1));

    auto method2 = ObjNativeMethod::make("readInt", readInt);
    module->addMethod(std::move(method2));

    auto method3 = ObjNativeMethod::make("readFloat", readFloat);
    module->addMethod(std::move(method3));

    auto method4 = ObjNativeMethod::make("printString", printString);
    module->addMethod(std::move(method4));
    return module;
}
