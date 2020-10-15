#pragma once

#include "Objects/ObjString.h"
#include "Vm/Common.h"

/**
 * @author minium2
 */
class Interpret {
public:
    /**
     * Interpret module with name "module name" in virtual machine.
     * Module must have method "main".
     * @return execution result.
     */
    static VmResult apply(const ObjString& moduleName, Vm &vm);
};