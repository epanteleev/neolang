#pragma once

#include <string>
#include "Objects/ObjFrwd.h"
#include "Vm/Common.h"

class Object {
public:
    explicit Object(ObjStringLiteral className) :
        m_name(std::move(className))
    {}

    virtual ~Object() = default;

    [[nodiscard]]
    inline virtual const std::string& objectName() const noexcept {
        return m_name;
    }

private:
    ObjStringLiteral m_name;
};
