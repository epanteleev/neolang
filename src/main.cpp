#include <Interpreter/Interpret.h>
#include <iostream>
#include <Modules/BaseIO.h>
#include "Parser/Parser.h"
#include "Vm/Vm.h"


int main(int argv, char** args) {
    if (argv != 2) {
        std::cerr << "Usage: neolang <file>." << std::endl;
        return 1;
    }
    std::filesystem::path file(args[1]);
    Vm vm;
    if (!Parser::parse(vm, file)) {
        return 1;
    }
    auto module = BaseIO::makeModule();
    vm.addModule(module);
    if(Interpret::apply(file.stem().string(), vm) != VmResult::SUCCESS) {
        vm.trace();
        return 1;
    }
    return 0;
}