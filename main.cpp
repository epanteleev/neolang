#include <Interpreter/Interpret.h>
#include <iostream>
#include <Modules/BaseIO.h>
#include "Parser/Parser.h"
#include "Vm/Vm.h"


int main(int argv, char** args) {
    Parser parser("D:\\test.nl");
    auto vm = parser.apply();
    auto module = BaseIO::makeModule();
    vm->addModule(module);
    if(Interpret::apply("Main", *vm) != VmResult::SUCCESS) {
        vm->trace();
        return 1;
    } else {
        return 0;
    }
}