#pragma once

#include <memory>
#include <Objects/ObjMethod.h>
#include <Objects/ObjNativeMethod.h>
#include "Objects/ObjNativeModule.h"

class BaseIO : public ObjNativeModule {
public:
    BaseIO() : ObjNativeModule("Io") {}

public:
    static VmResult printInt(Vm &vm) noexcept;

    static VmResult printFloat(Vm& vm) noexcept;

    static VmResult printString(Vm& vm) noexcept;

    static VmResult readInt(Vm& vm) noexcept;

    static VmResult readFloat(Vm& vm) noexcept;

public:
    static std::unique_ptr<ObjNativeModule> makeModule() noexcept;
};
