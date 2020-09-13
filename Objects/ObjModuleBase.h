#pragma once

#include <list>
#include <memory>
#include "Objects/Object.h"

class ObjModuleBase : public Object {
public:
    explicit ObjModuleBase(const std::string &moduleName) : Object(moduleName) {}

    [[nodiscard]]
    ObjMethodBase* findMethod(const std::string &name) const noexcept;

    [[nodiscard]]
    inline const std::string &moduleName() const noexcept {
        return objectName();
    }

protected:
    std::list<std::unique_ptr<ObjMethodBase>> m_methods{};
};
