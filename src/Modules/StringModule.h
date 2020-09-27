#pragma once

#include <memory>
#include <Objects/ObjMethod.h>
#include <Objects/ObjNativeMethod.h>
#include "Objects/ObjNativeModule.h"

class StringModule final : public ObjNativeModule {
public:
    StringModule() : ObjNativeModule("String") {}

    static VmResult printType(Vm &vm) noexcept;

    static VmResult concat(Vm& vm) noexcept;

public:
    static std::unique_ptr<ObjNativeModule> makeModule() noexcept {
        auto module = std::make_unique<StringModule>();

        auto method = ObjNativeMethod::make(*module, "concat", concat);
        module->addMethod(method);

        return module;
    }
};

struct StringInstance {
    StringModule *rtti;
    std::string str;
};