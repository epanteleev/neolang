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
    explicit ObjNativeMethod(const ObjModuleBase &module, ObjString moduleName, Native &func) :
            ObjMethodBase(module, std::move(moduleName)),
            m_func(std::move(func)) {}

    ObjNativeMethod(ObjNativeMethod &&module) noexcept:
            ObjMethodBase(module.m_module, std::move(module.m_name)),
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
    inline static std::unique_ptr<ObjNativeMethod> make(const ObjModuleBase &module,
                                                        const ObjString &moduleName,
                                                        Native func) noexcept {
        return std::make_unique<ObjNativeMethod>(module, moduleName, func);
    }

private:
    Native m_func;
};
