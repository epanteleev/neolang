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
private:
    Vm() = default;

public:
    static void registerModule(std::unique_ptr<ObjModule> &&module) noexcept {
        modules().addModule(std::move(module));
    }

    static void registerModule(std::unique_ptr<ObjNativeModule> &&module) noexcept {
        modules().addModule(std::move(module));
    }

    static ModuleBuffer &modules() noexcept {
        static ModuleBuffer m_modules;
        return m_modules;
    }

    static StringBuffer &strings() noexcept {
        static StringBuffer m_constantStrings;
        return m_constantStrings;
    }

public:

    [[nodiscard]]
    static const ObjString &findString(std::size_t idx) noexcept {
        return strings().find(idx);
    }

    [[nodiscard]]
    static std::size_t findStr(const char* str) noexcept {
        return Vm::strings().find(str); //Todo called copy constructor
    }
};
