#pragma once

#include <memory>
#include <list>

#include "Objects/Object.h"
#include "Objects/ObjMethodBase.h"
#include "Objects/ObjModuleBase.h"

class ModuleBuffer final {
public:
    ModuleBuffer() = default;
    ModuleBuffer(ModuleBuffer&) = delete;

    ~ModuleBuffer() = default;

    ObjModuleBase* findModule(const std::string& moduleName) noexcept;

    ObjMethodBase* findMethod(const std::string& moduleName, const std::string& name) noexcept;

    inline void addModule(std::unique_ptr<ObjModuleBase> &module) noexcept {
        m_methods.push_back(std::move(module));
    }

private:
    std::list<std::unique_ptr<ObjModuleBase>> m_methods;
};