#pragma once

#include <list>
#include <memory>
#include "Objects/Object.h"

/**
 * Base class for all module classes.
 * @author minium2
 */
class ObjModuleBase : public Object {
public:
    explicit ObjModuleBase(const ObjString &moduleName) : Object(moduleName) {}

    ObjModuleBase(ObjModuleBase&& module) noexcept :
        Object(module.moduleName()),
        m_methods(std::move(module.m_methods)) {}

    [[nodiscard]]
    ObjMethodBase* findMethod(const ObjString &name) const noexcept;

    [[nodiscard]]
    inline const ObjString &moduleName() const noexcept {
        return objectName();
    }

protected:
    std::list<std::unique_ptr<ObjMethodBase>> m_methods{};
};
