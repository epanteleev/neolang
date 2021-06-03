#pragma once

#include <utility>

#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"

class ObjMethodBase : public Object {
public:
    explicit ObjMethodBase(ObjString methodName) :
            Object(std::move(methodName)) {}

    ObjMethodBase(ObjMethodBase&& method) noexcept :
            Object(std::move(method.m_name)),
            m_module(method.m_module) {}

public:
    [[nodiscard]]
    inline const ObjString &methodName() const noexcept {
        return objectName();
    }

    [[nodiscard]]
    inline const ObjModuleBase &module() const noexcept {
        return *m_module;
    }

    [[nodiscard]]
    virtual bool isNative() const noexcept = 0;

    [[nodiscard]]
    virtual ObjMethod& asMethod() const noexcept = 0;

    [[nodiscard]]
    virtual ObjNativeMethod& asNativeMethod() const noexcept = 0;

    virtual VmResult apply(Environment &vm) noexcept = 0;

    inline void setModule(ObjModuleBase *module) noexcept {
        m_module = module;
    }

protected:
    const ObjModuleBase *m_module{};
};
