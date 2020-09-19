#pragma once

#include <list>
#include <memory>
#include "Objects/Object.h"

class ObjModuleBase : public Object {
public:
    explicit ObjModuleBase(const String &moduleName) : Object(moduleName) {}

    ObjModuleBase(ObjModuleBase&& module) noexcept :
        Object(module.moduleName()),
        m_methods(std::move(module.m_methods)) {}

    [[nodiscard]]
    ObjMethodBase* findMethod(const String &name) const noexcept;

    [[nodiscard]]
    inline const std::string &moduleName() const noexcept {
        return objectName();
    }

protected:
    std::list<std::unique_ptr<ObjMethodBase>> m_methods{};
};
