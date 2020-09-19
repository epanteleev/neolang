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
          return VmResult::TERMINATE;                                                        \
        }                                                                      \
      } while (false)

#define ZERO_DIVISION(vm, condition)                                          \
      do                                                                       \
      {                                                                        \
        if (!(condition))                                                      \
        {                                                                      \
          vm.vmError("Zero division.");                                                 \
          vm.trace();                                                          \
          return VmResult::ZERO_DIVISION;                                                        \
        }                                                                      \
      } while (false)

enum class VmResult {
    SUCCESS,
    TERMINATE,
    ZERO_DIVISION
};

class Vm {
public:
    Vm() = default;

    Vm(Vm &) = delete;

    ~Vm() = default;

public:

    inline void addModule(std::unique_ptr<ObjModule> &module) noexcept {
        m_modules.addModule(module);
    }

    inline void addModule(std::unique_ptr<ObjNativeModule> &module) noexcept {
        m_modules.addModule(module);
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

    [[nodiscard]]
    inline Value load(size_t idx) const noexcept {
        ASSERT(idx < MAX_LOCAL_VARS, "Invalid local variables index.");
        return m_local[idx];
    }

    inline void leave() noexcept {
        ASSERT(!m_callStack.empty(), "CallStack is empty.");
        const auto frame = m_callStack.top();
        m_callStack.pop();
        m_apiStack.drop(frame.savedSp());
    }

    void trace();

    void vmError(const std::string &message) noexcept;

    void perror(const std::string& basicString);

public:
    static constexpr size_t MAX_LOCAL_VARS = 4;

private:
    /** Virtual stack of virtual machine. */
    ApiStack m_apiStack;
    std::array<Value, MAX_LOCAL_VARS> m_local;

    CallStack m_callStack;
    ModuleBuffer m_modules;
};
