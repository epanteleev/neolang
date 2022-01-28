#include "Interpreter/BaselineInterpreter.h"
#include <iostream>

#include "Modules/BaseIO.h"
#include "Modules/StringModule.h"
#include "Parser/Parser.h"

int main(int argv, char** args) {
    if (argv != 2) {
        std::cerr << "Usage: neolang <file>." << std::endl;
        return 1;
    }
    std::filesystem::path file(args[1]);

    Vm vm{};
    try {
        Parser::parse(vm, file);
    } catch (std::exception& ex) {
        std::cerr << ex.what() <<  std::endl;
        return 1;
    }

    vm.registerModule(BaseIO::makeModule());
    vm.registerModule(StringModule::makeModule());

    BaselineInterpreter interpreter(vm);
    if(interpreter.apply(file.stem().string().c_str()) != VmResult::SUCCESS) {
        interpreter.trace();
        return 1;
    } else {
        return 0;
    }
}