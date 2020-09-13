#include "Vm.h"

static const char* typeToString(Type type) noexcept {
    switch (type) {
        case Type::INT32: return "i33";
        case Type::REF: return "ref";
        case Type::FLOAT32: return "f32";
        default: return "ud";
    }
    UNREACHABLE();
}

void Vm::trace() {
    fprintf(stderr, "[Vm trace]\n");
    fprintf(stderr, "[Api stack]\n");
    while (m_apiStack.nonEmpty()) {
        const auto value = m_apiStack.pop();
        fprintf(stderr, "\t%lu:%s\n", value.value(), typeToString(value.type()));
    }
    fprintf(stderr, "[Call stack]\n");
    while (!m_callStack.empty()) {
        const auto& method = m_callStack.top().method();
        fprintf(stderr, "\t%s::%s\n", method.module().moduleName().data(), method.methodName().data());
        m_callStack.pop();
    }
}

void Vm::vmError(const std::string& message) noexcept {
    fprintf(stderr, "Vm error: %s\n", message.data());
}

void Vm::perror(const std::string& message) {
    fprintf(stderr, "Error: %s\n", message.data());
}
