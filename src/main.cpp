#include "Interpreter/Interpret.h"
#include <iostream>
#include <Vm/Allocator/Collector.h>
#include <Parser/Parser.h>

#include "Modules/BaseIO.h"
#include "Modules/StringModule.h"
#include "Parser/NewParser.h"


int main(int argv, char** args) {
    if (argv != 2) {
        std::cerr << "Usage: neolang <file>." << std::endl;
        return 1;
    }
    std::filesystem::path file(args[1]);
    std::unique_ptr<Vm> vm;
    try {
        vm = NewParser::parse(file);
    } catch (ParseError& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    vm->addModule(BaseIO::makeModule());
    vm->addModule(StringModule::makeModule());
    if(Interpret::apply(file.stem().string().data(), *vm) != VmResult::SUCCESS) {
        vm->trace();
        return 1;
    }
    return 0;
}