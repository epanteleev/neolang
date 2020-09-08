#pragma once

#include <cstdlib>
#include "Object.h"

class ObjString: public Object {
public:

private:
    size_t m_length;
    char* m_cstr;
};
