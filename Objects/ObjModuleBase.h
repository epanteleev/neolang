#pragma once

#include <list>
#include <memory>
#include "Objects/Object.h"

class ObjModuleBase : public Object {
public:
    explicit ObjModuleBase(const ObjStringLiteral &moduleName) : Object(moduleName) {}

    [[nodiscard]]
    ObjMethodBase* findMethod(const ObjStringLiteral &name) const noexcept;

    [[nodiscard]]
    inline const std::string &moduleName() const noexcept {
        return objectName();
    }

protected:
    std::list<std::unique_ptr<ObjMethodBase>> m_methods{};
};
