#include <iostream>

#include "Vm/Vm.h"
#include <Modules/StringModule.h>
#include "Interpreter/Interpret.h"

int main() {
    SymbolTable table;
    table.push_back(ObjStringLiteral::make("add2and3"));
    table.push_back(ObjStringLiteral::make("Adder"));
    table.push_back(ObjStringLiteral::make("printType"));
    table.push_back(ObjStringLiteral::make("String"));
    Vm vm;

    auto module = ObjModule::make("Adder");

    auto method = ObjMethod::make(*module, "add2and3");
    method->addInst(Instruction(OpCode::iPUSH, Value(2)));
    method->addInst(Instruction(OpCode::iPUSH, Value(3)));
    method->addInst(Instruction(OpCode::iADD));
    method->addInst(Instruction(OpCode::RET));

    module->addMethod(method);

    vm.addModule(module);

    auto module1 = ObjModule::make("Main");
    auto method1 = ObjMethod::make(*module1, "main");
    method1->addInst(Instruction(OpCode::iPUSH, Value(7)));
    method1->addInst(Instruction(OpCode::CALLSTATIC, Value(1), Value(0)));
    method1->addInst(Instruction(OpCode::NEW, Value(3)));
    method1->addInst(Instruction(OpCode::CALLSTATIC, Value(3), Value(2)));
    module1->addMethod(method1);
    module1->registerConstants(table);
    vm.addModule(module1);
    auto string = StringModule::makeModule();
    vm.addNative(string);
    if(Interpret::apply("Main", vm)) {
        vm.trace();
    } else {
        std::cout << "Abort" << std::endl;
    }

    return 0;
}
