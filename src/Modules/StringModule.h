#pragma once

#include <memory>
#include <Objects/ObjMethod.h>
#include <Objects/ObjNativeMethod.h>
#include "Objects/ObjNativeModule.h"
/**
 * Module for working with string in language.
 * @author minium
 */
class StringModule final : public ObjNativeModule {
public:
    StringModule() : ObjNativeModule("String") {}

    static VmResult concat(Vm& vm) noexcept;

public:
    static std::unique_ptr<ObjNativeModule> makeModule() noexcept {
        auto module = std::make_unique<StringModule>();

        auto method = ObjNativeMethod::make("concat", concat);
        module->addMethod(std::move(method));

        return module;
    }
};

struct StringInstance {
    StringModule *rtti;
    std::string str;
};