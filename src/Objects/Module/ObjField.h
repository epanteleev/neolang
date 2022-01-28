#pragma once

#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"
#include "Vm/Value.h"

/**
 * Field of class.
 */
class ObjField final {
public:
    using size_type = std::size_t;
    using value_type = Value::Type;

public:
    explicit ObjField(size_type nameID, size_type offset, Value::Type type) :
            nameId(nameID),
            offset(offset),
            type(type) {}

public:
    size_type nameId;
    size_type offset;
    Value::Type type;
};