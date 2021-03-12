#pragma once

#include <functional>
#include <memory>

#include "Objects/Object.h"
#include "Objects/ObjMethodBase.h"

using Native = std::function<VmResult(Vm &)>;

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
    VmResult apply(Vm &vm) noexcept override;

    [[nodiscard]]
    inline bool isNative() const noexcept override { return true; }

public:
    inline static std::unique_ptr<ObjNativeMethod> make(const ObjString &moduleName, Native func) noexcept {
        return std::make_unique<ObjNativeMethod>(moduleName, func);
    }

private:
    Native m_func;
};
