#pragma once

#include <vector>
#include <string>
#include <map>
#include <Instruction.h>

#include "Object.h"
#include "ObjFrwd.h"

typedef void (*Natives)(Vm* obj);

class ObjMethod: public Object {
public:

public:
    std::vector<Instruction> instList;
};

using SymbolTable = std::map<std::string, Natives>;