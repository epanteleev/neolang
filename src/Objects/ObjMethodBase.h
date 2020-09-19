#pragma once

#include <utility>

#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"


class ObjMethodBase : public Object {
public:
    explicit ObjMethodBase(const ObjModuleBase &mModule, const String &moduleName,
                           String  methodName) :
            Object(moduleName),
            m_module(mModule),
            m_methodName(std::move(methodName)) {}

    ObjMethodBase(ObjMethodBase&& method) noexcept :
            Object(method.m_methodName),
            m_module(method.m_module),
            m_methodName(std::move(method.m_methodName)) {}

    [[nodiscard]]
    inline const String &methodName() const noexcept {
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
    String m_methodName;
};
