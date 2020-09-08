#include "Vm.h"
#include "Instruction.h"

Instruction Vm::currentInst() const {
    return m_insts[ip];
}

void Vm::trace() {
    fprintf(stderr, "...Vm trace...\n");
    fprintf(stderr, "Stack: \n");
    for (Value i = m_apiStack.pop(); m_apiStack.empty(); m_apiStack.pop()) {
        fprintf(stderr, "%lu\n", i.value());
    }
}

