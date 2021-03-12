#pragma once

#include <memory>
#include <list>

#include "Objects/ObjModuleBase.h"
#include "Objects/ObjModule.h"
#include "Objects/ObjNativeModule.h"

/**
 * Represent buffer of modules.
 * @author minium2
 */
class ModuleBuffer final {
public:
    ModuleBuffer() = default;

    ModuleBuffer(ModuleBuffer &) = delete;

    ~ModuleBuffer() = default;

public:
    /**
     * Find module by module name.
     * @return nullptr if module wasn't found.
     */
    ObjModuleBase *findModule(const ObjString &moduleName) noexcept;

    /**
     * Find method by module and method names.
     * @return nullptr if method wasn't found.
     */
    ObjMethodBase *findMethod(const ObjString &moduleName, const ObjString &name) noexcept;

    inline void addModule(std::unique_ptr<ObjNativeModule> &&module) noexcept {
        m_modules.push_back(std::move(module));
    }

    inline void addModule(std::unique_ptr<ObjModule> &&module) noexcept {
        m_modules.push_back(std::move(module));
    }

private:
    std::list<std::unique_ptr<ObjModuleBase>> m_modules;
};