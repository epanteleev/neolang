#pragma once

#include <cstdlib>
#include <cstring>
#include "Common.h"
#include <algorithm>
#include "Object.h"
#include "ObjFrwd.h"

class ObjString: public Object {
public:
    static Value make(const char* cstr) noexcept {
        size_t length = strlen(cstr);
        auto* str =  new ObjString(); //(ObjString*) malloc(sizeof(ObjString) + length);
        str->m_cstr = std::string(cstr);
        str->m_name = std::string("ObjString");
        return Value((uintptr_t)str);
    }

    inline const std::string& str() const noexcept {
        return m_cstr;
    }

private:
    std::string m_cstr;
};
