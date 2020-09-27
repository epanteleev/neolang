#pragma once

#include <Vm/ApiStack.h>
#include <Vm/Vm.h>

class Collector {
public:
    Collector(ApiStack &stack, Locals &locals) :
            m_apiStack(stack),
            m_locals(locals) {}

    void collect() noexcept {
        //Todo: Unimplemented yet.
    }

private:
    ApiStack &m_apiStack;
    Locals &m_locals;
};