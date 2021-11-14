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

    try {
        Parser::parse(file);
    } catch (std::exception& ex) {
        std::cerr << ex.what() <<  std::endl;
        return 1;
    }


    Vm::registerModule(BaseIO::makeModule());
    Vm::registerModule(StringModule::makeModule());

    BaselineInterpreter interpreter;
    if(interpreter.apply(file.stem().string().c_str()) != VmResult::SUCCESS) {
        interpreter.trace();
        return 1;
    } else {
        return 0;
    }
}