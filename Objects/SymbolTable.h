#pragma once
#include <map>

#include "ObjFrwd.h"

typedef void (*NativeFunc)(Vm *obj);

using SymbolTable = std::map<std::string, NativeFunc>;