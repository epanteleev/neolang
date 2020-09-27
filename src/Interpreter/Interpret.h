#pragma once

#include "Objects/ObjString.h"
#include "Vm/Common.h"

class Interpret {
public:
    static VmResult apply(const ObjString& moduleName, Vm &vm);
};