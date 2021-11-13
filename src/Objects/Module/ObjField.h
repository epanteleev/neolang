#pragma once

#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"
#include "Vm/Value.h"

/**
 * Field of class.
 */
class ObjField {
public:
    explicit ObjField(std::size_t nameID, std::size_t offset, Value::Type type) :
            nameId(nameID),
            offset(offset),
            type(type) {}

public:
    std::size_t nameId;
    std::size_t offset;
    Value::Type type;
};