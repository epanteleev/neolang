#include <iostream>
#include <vector>
#include <Vm.h>
#include <map>
#include <ObjModule.h>
#include "Interpreter/Interpret.h"
#include "Common.h"
#include "ObjString.h"
#include "ObjMethod.h"

static void println(Vm *vm) {
    Object *obj = vm->stack().pop().toObject();
    if (obj->m_name == "ObjString") {
        auto cstr = (ObjString *) obj;
        printf("%s", cstr->str().data());
    } else {
        UNREACHABLE();
    }
}

int main() {

    std::vector<Instruction> inst = {
            Instruction(OpCode::iPUSH, Value(2)),
            Instruction(OpCode::iPUSH, Value(3)),
            Instruction(OpCode::iADD),
            Instruction(OpCode::iSTORE, Value(0)),
            Instruction(OpCode::iPUSH, Value(3)),
            Instruction(OpCode::iPUSH, ObjString::make("Hello World")),
            Instruction(OpCode::CALL, ObjString::make("println"))
    };

    SymbolTable symTable = {
            {"println", println}
    };

    Vm vm(inst, symTable);
    Interpret::apply(vm);
    vm.trace();


    auto method = ObjMethod::make("add");
    method->addInst(Instruction(OpCode::iPUSH, Value(2)));
    method->addInst(Instruction(OpCode::iPUSH, Value(3)));
    method->addInst(Instruction(OpCode::iADD));

    auto module = ObjModule::make();
    module->addMethod(method);
    return 0;
}
