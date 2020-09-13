#pragma once


#include <functional>
#include <memory>
#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"

using Native = std::function<void(Vm &)>;

class ObjNativeMethod : public Object {
public:
    explicit ObjNativeMethod(const ObjNativeModule &module, const std::string &moduleName, Native &func) :
            Object(moduleName),
            m_module(module),
            m_methodName(moduleName),
            m_func(std::move(func)) {}

    ObjNativeMethod(ObjNativeMethod &&module) noexcept:
            Object(module.m_methodName),
            m_module(module.m_module),
            m_methodName(std::move(module.m_methodName)),
            m_func(std::move(module.m_func)) {}

    ObjNativeMethod(ObjNativeMethod &) = delete;

    ~ObjNativeMethod() override = default;

    inline const std::string &methodName() const noexcept {
        return m_methodName;
    }

    inline void operator()(Vm& vm) noexcept {
        m_func(vm);
    }
public:
    inline static std::unique_ptr<ObjNativeMethod> make(const ObjNativeModule &module, const std::string &moduleName, Native func) noexcept {
        return std::make_unique<ObjNativeMethod>(module, moduleName, func);
    }

private:
    const ObjNativeModule &m_module;
    std::string m_methodName;
    Native m_func;
};
