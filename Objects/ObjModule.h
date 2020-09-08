#pragma once

#include <list>
#include "Object.h"
#include "ObjMethod.h"

class ObjModule final: public Object {
public:
    ObjModule() = default;

public:
    std::list<ObjModule*> m_imports;
    std::list<ObjMethod*> m_methods;
    std::map<std::string, Value> m_fields;
};
