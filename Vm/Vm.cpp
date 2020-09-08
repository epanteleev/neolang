#include "Vm.h"
#include "Instruction.h"

Instruction Vm::currentInst() const {
    return m_insts[ip];
}

void Vm::trace() {
    fprintf(stderr, "...Vm trace...\n");
    fprintf(stderr, "Stack: \n");
    while (m_apiStack.nonEmpty()) {
        fprintf(stderr, "%lu\n", m_apiStack.pop().value());
    }
}

