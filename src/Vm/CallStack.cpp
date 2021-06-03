#include "Vm/CallStack.h"
#include "Objects/ObjModule.h"

void CallStack::stacktrace() {
    while (!m_stack.empty()) {
        const auto& method = m_stack.top().method();
        fprintf(stderr, "\t%s::%s\n", method.module().moduleName().cstr(), method.methodName().cstr());
        m_stack.pop();
    }
}
