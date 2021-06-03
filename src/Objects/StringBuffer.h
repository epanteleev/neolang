#pragma once

#include <memory>
#include <vector>
#include "Objects/ObjFrwd.h"
#include "Objects/ObjString.h"

/**
 * Map String to index in symbol table.
 */
using StringBuffer = std::vector<ObjString>; //Todo impl as hash table