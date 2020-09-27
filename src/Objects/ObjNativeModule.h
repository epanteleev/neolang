#pragma once

#include <list>

#include "Objects/Object.h"
#include "Objects/ObjNativeMethod.h"
#include "Objects/ObjModuleBase.h"

class ObjNativeModule : public ObjModuleBase {
public:
    explicit ObjNativeModule(const ObjString &className) :
            ObjModuleBase(className) {}

    ObjNativeModule(ObjNativeModule &&module) noexcept:
            ObjModuleBase(std::move(module)) {}

    ~ObjNativeModule() override = default;

    inline void addMethod(std::unique_ptr<ObjNativeMethod> &method) noexcept {
        m_methods.push_back(std::move(method));
    }
};