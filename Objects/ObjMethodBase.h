#pragma once

#include <utility>

#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"


class ObjMethodBase : public Object {
public:
    explicit ObjMethodBase(const ObjModuleBase &mModule, const ObjStringLiteral &moduleName,
                           const ObjStringLiteral& methodName) :
            Object(moduleName),
            m_module(mModule),
            m_methodName(methodName) {}

    [[nodiscard]]
    inline const std::string &methodName() const noexcept {
        return m_methodName;
    }

    [[nodiscard]]
    inline const ObjModuleBase &module() const noexcept {
        return m_module;
    }

    [[nodiscard]]
    virtual bool isNative() const noexcept = 0;

    virtual VmResult apply(Vm &vm) noexcept = 0;

protected:
    const ObjModuleBase &m_module;
    ObjStringLiteral m_methodName;
};
