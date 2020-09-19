#pragma once

#include <memory>
#include <Objects/ObjMethod.h>
#include <Objects/ObjNativeMethod.h>
#include "Objects/ObjNativeModule.h"

class IOModule {
public:
    static VmResult printInt(Vm &vm) noexcept;

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
