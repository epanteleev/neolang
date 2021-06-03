#pragma once

#include <array>

#include "Objects/ObjNativeModule.h"
#include "Objects/ModuleBuffer.h"

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

    /**
     * Insert given str to string pull.
     * @return position str in string buffer.
     */
    static size_t addStringConstant(ObjString &&str) noexcept {
        strings().push_back(std::move(str));
        return strings().size() - 1;
    }

    [[nodiscard]]
    static const ObjString *findString(size_t idx) noexcept {
        if (strings().size() <= idx) {
            return nullptr;
        } else {
            return &strings()[idx];
        }
    }
};
