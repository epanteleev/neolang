#pragma once

#include <cstdlib>
#include <cstring>
#include "Common.h"
#include <algorithm>
#include <utility>
#include "Object.h"
#include "ObjFrwd.h"

class ObjString : public Object {
public:
    ObjString(std::string  string):
        Object("ObjString"),
        m_cstr(std::move(string))
    {}

    static Value make(const std::string& string) noexcept {
        return Value((uintptr_t) new ObjString(string));
    }

    inline const std::string &str() const noexcept {
        return m_cstr;
    }

private:
    std::string m_cstr;
};
