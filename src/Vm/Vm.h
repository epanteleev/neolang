#pragma once

#include <array>

#include "Objects/Module/ObjNativeModule.h"
#include "Objects/Module/ModuleBuffer.h"

#include "Vm/Environment.h"

enum class VmResult {
    SUCCESS,
    TERMINATE,
    ZERO_DIVISION
};

class Vm final {
public:
    Vm() = default;
    ~Vm() = default;
    Vm(Vm&) = delete;

public:
    void registerModule(std::unique_ptr<ObjModule> module) noexcept {
        modules().addModule(std::move(module));
    }

    void registerModule(std::unique_ptr<ObjNativeModule> module) noexcept {
        modules().addModule(std::move(module));
    }

    ModuleBuffer &modules() noexcept {
        return m_modules;
    }

    StringBuffer &strings() noexcept  {
        return m_constantStrings;
    }

public:
    [[nodiscard]]
    const ObjString &findString(std::size_t idx) noexcept {
        return strings().find(idx);
    }

    [[nodiscard]]
    std::size_t findStr(const char* str) noexcept {
        return Vm::strings().find(str); //Todo called copy constructor
    }

private:
    ModuleBuffer m_modules;
    StringBuffer m_constantStrings;
};
