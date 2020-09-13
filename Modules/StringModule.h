#pragma once

#include "Objects/ObjNativeModule.h"

class StringModule final : public ObjNativeModule {
public:
    StringModule() : ObjNativeModule("String") {}

    void *newInstance(Vm &vm) noexcept override {

    }

    bool finalize(Vm &vm) noexcept override {
        return false;
    }
};


struct StringInstance {
    StringModule *rtti;
    char ch[0];
};