//
// Created by user on 08.09.2020.
//

#include <map>
#include "Interpret.h"

static std::map<OpCode, Interpret::Actions> handlers = {
        {OpCode::iADD, iAdd::apply},
        {OpCode::iPUSH, iPush::apply},
        {OpCode::iSTORE, iStore::apply}
};
void Interpret::apply(Vm &vm) {
    for (;vm.hasNext(); vm.next()) {
        handlers[vm.currentInst().opCode](vm);
    }
}
