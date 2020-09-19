#include "Modules/IOModule.h"

#include "Vm/Vm.h"
#include <iostream>

VmResult IOModule::printInt(Vm &vm) noexcept {
    auto value = vm.load(0);
    std::cout << value.toInt32();
    return VmResult::SUCCESS;
}
