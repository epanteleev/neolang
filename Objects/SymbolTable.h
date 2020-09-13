#pragma once

#include <memory>

#include "Objects/ObjFrwd.h"
#include "Objects/ObjStringLiteral.h"

typedef void (*NativeFunc)(Vm *obj);

/**
 * Map ObjStringLiteral to index in symbol table.
 */
using SymbolTable = std::vector<std::unique_ptr<ObjStringLiteral>>;