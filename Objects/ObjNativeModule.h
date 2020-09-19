#pragma once
#include <list>

#include "Objects/Object.h"
#include "Objects/ObjNativeMethod.h"
#include "Objects/ObjModuleBase.h"

class ObjNativeModule : public ObjModuleBase {
public:
    explicit ObjNativeModule(const std::string &className) :
            ObjModuleBase(className) {}

    ~ObjNativeModule() override = default;

    void addMethod(std::unique_ptr<ObjNativeMethod> &method) noexcept {
        m_methods.push_back(std::move(method));
    }
};