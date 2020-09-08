#include <iostream>
#include <vector>
#include <Instruction.h>
#include <Vm.h>
#include "Interpreter/Interpret.h"
#include "Common.h"
#define DEBUG

int main() {
    std::vector<Instruction> inst = {
            Instruction(OpCode::iPUSH, Value(2)),
            Instruction(OpCode::iPUSH, Value(3)),
            Instruction(OpCode::iADD),
            Instruction(OpCode::iSTORE, Value(0)),
            Instruction(OpCode::iPUSH, Value(3))
    };
    Vm vm(inst);
    Interpret::apply(vm);
    vm.trace();
    return 0;
}
