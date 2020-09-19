#pragma once

#include <memory>

#include "Objects/ObjFrwd.h"

typedef void (*NativeFunc)(Vm *obj);

/**
 * Map ObjStringLiteral to index in symbol table.
 */
using StringBuffer = std::vector<ObjStringLiteral>;