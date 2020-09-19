#pragma once

#include <memory>
#include <Objects/ObjMethod.h>
#include <Objects/ObjNativeMethod.h>
#include "Objects/ObjNativeModule.h"

class StringModule final : public ObjNativeModule {
public:
    StringModule() : ObjNativeModule("String") {}

    static VmResult printType(Vm &vm) noexcept;

    static VmResult constr(Vm &vm) noexcept;

public:
    static std::unique_ptr<ObjNativeModule> makeModule() noexcept {
        auto module = std::make_unique<StringModule>();

        auto method = ObjNativeMethod::make(*module, "printType",
                                            printType);
        module->addMethod(method);

        auto method1 = ObjNativeMethod::make(*module, "<new>", constr);
        module->addMethod(method1);
        return module;
    }
};

struct StringInstance {
    StringModule *rtti;
    std::string str;
};