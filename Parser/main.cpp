#include <Interpreter/Interpret.h>
#include <iostream>
#include "Parser/Parser.h"
#include "Vm/Vm.h"


int main() {
    Parser parser("D:\\test.nl");
    auto vm = parser.apply();
    if(Interpret::apply("Main", *vm) == VmResult::SUCCESS) {
        vm->trace();
    } else {
        std::cout << "Abort" << std::endl;
    }

    return 0;
}