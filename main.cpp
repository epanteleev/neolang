#include <iostream>
#include <vector>
#include "Vm/Vm.h"
#include <map>
#include <Objects/ObjModule.h>
#include <Objects/SymbolTable.h>
#include "Interpreter/Interpret.h"
#include "Vm/Common.h"
#include "Objects/ObjStringLiteral.h"
#include "Objects/ObjMethod.h"

static void println(Vm *vm) {
    Object *obj = vm->stack().pop().toObject();
    if (obj->objectName() == "ObjStringLiteral") {
        auto cstr = (ObjStringLiteral *) obj;
        printf("%s", cstr->str().data());
    } else {
        UNREACHABLE();
    }
}

int main() {
    SymbolTable table;
    table.push_back(ObjStringLiteral::make("add2and3"));
    table.push_back(ObjStringLiteral::make("Adder"));
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

    module1->addMethod(method1);
    module1->registerConstants(table);
    vm.addModule(module1);
    if(Interpret::apply("Main", vm)) {
        vm.trace();
    } else {
        std::cout << "Abort" << std::endl;
    }

    return 0;
}
