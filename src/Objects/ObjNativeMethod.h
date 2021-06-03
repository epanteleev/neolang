#pragma once

#include <functional>
#include <memory>

#include "Objects/Object.h"
#include "Objects/ObjMethodBase.h"

using Native = std::function<VmResult(Environment &)>;

/**
 * Represent native method of programming language.
 * To create a new module, you need to inherit.
 * @author minium2
 */
class ObjNativeMethod : public ObjMethodBase {
public:
    explicit ObjNativeMethod(ObjString moduleName, Native &func) :
            ObjMethodBase(std::move(moduleName)),
            m_func(std::move(func)) {}

    ObjNativeMethod(ObjNativeMethod &&module) noexcept:
            ObjMethodBase(std::move(module.m_name)),
            m_func(std::move(module.m_func)) {}

    ObjNativeMethod(ObjNativeMethod &) = delete;

    ~ObjNativeMethod() override = default;

public:
    /**
     * Call this method.
     * @return result of work this method.
     */
    VmResult apply(Environment &env) noexcept override;

    [[nodiscard]]
    ObjMethod& asMethod() const noexcept override {
        UNREACHABLE();
    }

    [[nodiscard]]
    inline ObjNativeMethod& asNativeMethod() const noexcept override {
        return static_cast<ObjNativeMethod&>(const_cast<ObjNativeMethod &>(*this));
    }

    [[nodiscard]]
    inline bool isNative() const noexcept override { return true; }

public:
    inline static std::unique_ptr<ObjNativeMethod> make(const ObjString &moduleName, Native func) noexcept {
        return std::make_unique<ObjNativeMethod>(moduleName, func);
    }

private:
    Native m_func;
};
