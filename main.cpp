#include <iostream>
#include <vector>
#include <Vm.h>
#include <map>
#include "Interpreter/Interpret.h"
#include "Common.h"
#include "ObjString.h"
#include "ObjMethod.h"

#define DEBUG

static void println(Vm* vm) {
    Object* obj = vm->stack().pop().toObject();
    if (obj->m_name == "ObjString") {
        auto cstr = (ObjString*)obj;
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
    return 0;
}
