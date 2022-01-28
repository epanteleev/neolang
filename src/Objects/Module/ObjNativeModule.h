#pragma once

#include <list>

#include "Objects/Object.h"
#include "Objects/Method/ObjNativeMethod.h"
#include "Objects/Module/ObjModuleBase.h"

class ObjNativeModule : public ObjModuleBase {
public:
    explicit ObjNativeModule(ObjString className) :
            ObjModuleBase(std::move(className)) {}

    ObjNativeModule(ObjNativeModule &&module) noexcept:
            ObjModuleBase(std::move(module)) {}

    ~ObjNativeModule() override = default;

public:
    inline void addMethod(std::unique_ptr<ObjNativeMethod> &&method) noexcept {
        m_methods.push_back(std::move(method));
    }

    [[nodiscard]]
    const ObjModule &asModule() const noexcept override {
        UNREACHABLE();
    }

    [[nodiscard]]
    ModuleType moduleType() const noexcept override {
        return ModuleType::NATIVE;
    }

    [[nodiscard]]
    const ObjNativeModule & asNativeModule() const noexcept override {
        return *this;
    }
};