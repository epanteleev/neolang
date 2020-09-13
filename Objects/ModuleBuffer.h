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

    ObjModuleBase* findModule(const std::string& moduleName) {
        auto pred = [&](const std::unique_ptr<ObjModuleBase> &i) { return (*i).moduleName() == moduleName; };
        const auto module = std::find_if(m_methods.begin(), m_methods.end(), pred);
        if (module != m_methods.end()) {
            return module->get();
        } else {
            return nullptr;
        }
    }

    ObjMethodBase* findMethod(const std::string& moduleName, const std::string& name) {
        const auto module = findModule(moduleName);
        if (module != nullptr) {
            return (*module).findMethod(name);
        } else {
            return nullptr;
        }
    }

    inline void addModule(std::unique_ptr<ObjModuleBase> &module) noexcept {
        m_methods.push_back(std::move(module));
    }

private:
    std::list<std::unique_ptr<ObjModuleBase>> m_methods;
};