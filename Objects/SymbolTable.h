#pragma once
#include <map>

#include "ObjFrwd.h"

typedef void (*Natives)(Vm *obj);

using SymbolTable = std::map<std::string, Natives>;