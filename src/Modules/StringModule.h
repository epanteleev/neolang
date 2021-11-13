#pragma once

#include <memory>
#include <Objects/Method/ObjMethod.h>
#include <Objects/Method/ObjNativeMethod.h>
#include "Objects/Module/ObjNativeModule.h"
/**
 * Module for working with string in language.
 * @author minium
 */
class StringModule final : public ObjNativeModule {
public:
    StringModule() : ObjNativeModule("String") {}

    static VmResult concat(Environment& vm) noexcept;

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