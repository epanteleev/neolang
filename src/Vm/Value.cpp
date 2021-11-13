#include "Vm/Value.h"
#include <cstring>

Value::Type Value::stringToType(const char *str) noexcept {
    if (strcmp(str, I32) == 0) return Type::INT32;
    else if (strcmp(str, U64) == 0) return Type::UINT64;
    else if (strcmp(str, REF) == 0) return Type::REF;
    else if (strcmp(str, F32) == 0) return Type::FLOAT32;
    else if (strcmp(str, F64) == 0) return Type::FLOAT64;
    else if (strcmp(str, BOOL) == 0) return Type::BOOL;
    else return Type::UNDEFINED;
}
