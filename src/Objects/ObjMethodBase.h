#pragma once

#include <utility>

#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"


class ObjMethodBase : public Object {
public:
    explicit ObjMethodBase(const ObjModuleBase &mModule, ObjString methodName) :
            Object(std::move(methodName)),
            m_module(mModule) {}

    ObjMethodBase(ObjMethodBase&& method) noexcept :
            Object(std::move(method.m_name)),
            m_module(method.m_module) {}

    [[nodiscard]]
    inline const ObjString &methodName() const noexcept {
        return objectName();
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
};
