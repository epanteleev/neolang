#pragma once
#include "Vm/Value.h"

/**
 * Represent instance of module.
 */
class Instance {
public:
    ObjModuleBase *clazz;
    Value fields[0];
};
