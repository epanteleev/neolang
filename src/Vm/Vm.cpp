#include <Vm/Allocator/RootSet.h>
#include "Vm/Vm.h"

void Vm::trace() {
    fprintf(stderr, "[Vm trace]\n");
    fprintf(stderr, "[Api stack]\n");
    for (auto& i : m_apiStack) {
        fprintf(stderr, "\t%lu:%s\n", i.value(), typeToString(i.type()));
    }
    fprintf(stderr, "[Call stack]\n");
    while (!m_callStack.empty()) {
        const auto& method = m_callStack.top().method();
        fprintf(stderr, "\t%s::%s\n", method.module().moduleName().cstr(), method.methodName().cstr());
        m_callStack.pop();
    }
}

void Vm::vmError(const ObjString& message) noexcept {
    fprintf(stderr, "Vm error: %s\n", message.cstr());
}

Vm::~Vm() {
    RootSet::set().finalize();
}


