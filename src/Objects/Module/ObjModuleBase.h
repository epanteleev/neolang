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
    explicit ObjModuleBase(ObjString moduleName) : Object(std::move(moduleName)) {}

    ObjModuleBase(ObjModuleBase&& module) noexcept :
        Object(std::move(module.m_name)),
        m_methods(std::move(module.m_methods)) {}

public:
    [[nodiscard]]
    virtual const ObjModule& asModule() const noexcept = 0;

    [[nodiscard]]
    virtual const ObjNativeModule& asNativeModule() const noexcept = 0;

    [[nodiscard]]
    ObjMethodBase* findMethod(const ObjString &name) const noexcept;

    [[nodiscard]]
    inline const ObjString &moduleName() const noexcept {
        return objectName();
    }

protected:
    std::list<std::unique_ptr<ObjMethodBase>> m_methods{};
};
