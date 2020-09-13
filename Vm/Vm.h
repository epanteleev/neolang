#pragma once

#include <stack>
#include <vector>
#include <array>
#include <map>

#include <Objects/ObjNativeModule.h>
#include <Objects/ModuleBuffer.h>
#include "Vm/Value.h"
#include "Vm/ApiStack.h"
#include "Objects/ObjMethod.h"
#include "Vm/Instruction.h"
#include "Objects/ObjModule.h"
#include "Vm/Frame.h"

#define TRACE(vm, condition, message)                                          \
      do                                                                       \
      {                                                                        \
        if (!(condition))                                                      \
        {                                                                      \
          vm.vmError(message);                                                 \
          vm.trace();                                                          \
          return false;                                                        \
        }                                                                      \
      } while (false)


class Vm {
public:
    Vm() = default;

    Vm(Vm &) = delete;

    ~Vm() = default;

    inline void addModule(std::unique_ptr<ObjModule> &module) noexcept {
        m_modules.addModule(reinterpret_cast<std::unique_ptr<ObjModuleBase> &>(module));
    }

    inline void addModule(std::unique_ptr<ObjNativeModule> &module) noexcept {
        m_modules.addModule(reinterpret_cast<std::unique_ptr<ObjModuleBase> &>(module));
    }
    inline ApiStack &stack() noexcept {
        return m_apiStack;
    }

    inline Frame &frame() noexcept {
        return m_callStack.top();
    }

    inline CallStack &callStack() noexcept {
        return m_callStack;
    }

    inline ModuleBuffer &modules() noexcept {
        return m_modules;
    }

    inline void store(Value val, size_t idx) noexcept {
        m_local[idx] = val;
    }

    void trace();

    void vmError(const std::string &message) noexcept;

    void perror(const std::string& basicString);

private:
    /** Virtual stack of virtual machine. */
    ApiStack m_apiStack;
    std::array<Value, 4> m_local;

    CallStack m_callStack;
    ModuleBuffer m_modules;
};
