#pragma once

#include "Objects/Object.h"

class ObjNativeModule : public Object {
public:
    ObjNativeModule(const std::string &className) :
            Object(className) {}

    virtual void* newInstance(Vm& vm) noexcept = 0;

    virtual bool finalize(Vm& vm) noexcept = 0;

    virtual ~ObjNativeModule() = default;
};