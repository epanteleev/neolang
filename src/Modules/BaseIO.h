#pragma once

#include <memory>
#include <Objects/ObjMethod.h>
#include <Objects/ObjNativeMethod.h>
#include "Objects/ObjNativeModule.h"

class BaseIO : public ObjNativeModule {
public:
    BaseIO() : ObjNativeModule("Io") {}

public:
    static VmResult printInt(Environment &vm) noexcept;

    static VmResult printFloat(Environment& vm) noexcept;

    static VmResult printString(Environment& vm) noexcept;

    static VmResult readInt(Environment& vm) noexcept;

    static VmResult readFloat(Environment& vm) noexcept;

public:
    static std::unique_ptr<ObjNativeModule> makeModule() noexcept;
};
