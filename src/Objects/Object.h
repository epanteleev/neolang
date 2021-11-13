#pragma once

#include "Objects/ObjFrwd.h"
#include "Objects/ObjString.h"

/**
 * Base class for all virtual machine represent classes.
 * @author minium2
 */
class Object {
public:
    explicit Object(ObjString&& name) :
        m_name(std::move(name))
    {}

    virtual ~Object() = default;

    [[nodiscard]]
    inline virtual const ObjString& objectName() const noexcept {
        return m_name;
    }

protected:
    ObjString m_name;
};
