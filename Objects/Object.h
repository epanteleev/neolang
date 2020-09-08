#pragma once

#include <string>
#include <utility>
#include "ObjFrwd.h"

class Object {
public:
    Object(std::string className) :
        m_name(std::move(className))
    {}

    Object() = default;

public:
    std::string m_name;
};
