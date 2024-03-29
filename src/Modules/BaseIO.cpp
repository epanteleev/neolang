#include "Modules/BaseIO.h"

#include "Vm/Vm.h"
#include <iostream>

VmResult BaseIO::printInt(Environment &env) noexcept {
    auto value = env.locals().load(0);
    std::cout << value.toInt32() << std::endl;
    return VmResult::SUCCESS;
}

VmResult BaseIO::printFloat(Environment &env) noexcept {
    auto value = env.locals().load(0);
    std::cout << value.toFloat32() << std::endl;
    return VmResult::SUCCESS;
}

VmResult BaseIO::readInt(Environment &env) noexcept {
    int i = 0;
    std::cin >> i;
    env.stack().push(Value(i));
    return VmResult::SUCCESS;
}

VmResult BaseIO::readFloat(Environment &env) noexcept {
    float i = 0;
    std::cin >> i;
    env.stack().push(Value(i));
    return VmResult::SUCCESS;
}

VmResult BaseIO::printString(Environment &env) noexcept {
    auto value = env.locals().load(0);
    ObjStringViewer ptr(value);
    std::cout << ptr << std::endl;
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
