#include "Interpreter/Interpret.h"
#include <iostream>
#include <Vm/Allocator/Collector.h>

#include "Modules/BaseIO.h"
#include "Modules/StringModule.h"
#include "Parser/Parser.h"


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
    auto stringModule = StringModule::makeModule();
    vm.addModule(stringModule);
    if(Interpret::apply(file.stem().string().data(), vm) != VmResult::SUCCESS) {
        vm.trace();
        return 1;
    }
    return 0;
}