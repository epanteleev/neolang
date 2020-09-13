#pragma once

#include <memory>
#include "Vm/Common.h"
#include "Objects/Object.h"
#include "Objects/ObjFrwd.h"

class ObjStringLiteral : public Object {
public:
    explicit ObjStringLiteral(std::string string) :
            Object("ObjStringLiteral"),
            m_cstr(std::move(string)) {}

    ObjStringLiteral(ObjStringLiteral &string) :
            Object("ObjStringLiteral") {
        ASSERT(false, "Called copy constructor");
    }

    ObjStringLiteral(ObjStringLiteral &&string) noexcept:
            Object("ObjStringLiteral"),
            m_cstr(std::move(string.m_cstr)) {}

public:
    static std::unique_ptr<ObjStringLiteral> make(const std::string &string) noexcept {
        return std::make_unique<ObjStringLiteral>(string);
    }

    inline const std::string &str() const noexcept {
        return m_cstr;
    }

private:
    std::string m_cstr;
};
