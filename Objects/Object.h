#pragma once

#include <string>
#include "Objects/ObjFrwd.h"

class Object {
public:
    explicit Object(std::string className) :
        m_name(std::move(className))
    {}

    virtual ~Object() = default;

    [[nodiscard]]
    inline virtual const std::string& objectName() const noexcept {
        return m_name;
    }

private:
    std::string m_name;
};
