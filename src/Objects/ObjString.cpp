#include "Objects/ObjString.h"
#include "Vm/Allocator/Allocator.h"

#include <iostream>
#include <cstdint>
#include <cstring>

struct FlatString {
    size_t rtti;
    size_t length;
    char cstr[0];

    inline void *operator new(size_t size, size_t length) {
        return (void *) Allocator::New(size + length + 1);
    }

    inline void operator delete(void *ptr) {
        Allocator::Delete(ptr);
    }
};

ObjString::ObjString(const char *c) {
    if (c == nullptr) {
        UNREACHABLE();
    }
    size_t length = strlen(c);
    m_string = new(length) FlatString();
    m_string->length = length;
    std::copy(c, c + length, m_string->cstr);
    m_string->cstr[length] = '\0';
}

ObjString::ObjString(const ObjString &s) {
    size_t length = s.len();
    m_string = new(length) FlatString();
    std::copy(s.m_string->cstr, s.m_string->cstr + s.m_string->length, m_string->cstr);
    m_string->length = length;
    m_string->cstr[length] = '\0';
}


ObjString::~ObjString() {
    reset();
}

size_t ObjString::index(char c) const noexcept {
    for (size_t j = 0; j < m_string->length; j++) {
        if (m_string->cstr[j] == c) return j;
    }
    return INT64_MAX;
}


std::ostream &operator<<(std::ostream &os, const ObjString &s) {
    os << reinterpret_cast<char *>(s.m_string->cstr);
    return os;
}

ObjString &ObjString::operator=(const ObjString &s) {
    if (*this == s) {
        return *this;
    }
    reset();
    size_t length = s.m_string->length;
    m_string = new(length) FlatString();
    std::copy(s.m_string->cstr, s.m_string->cstr + length, m_string->cstr);
    m_string->length = length;
    return *this;
}

ObjString &ObjString::operator+=(const ObjString &s) {
    size_t len = this->len() + s.len();
    auto *str = new(len) FlatString();
    std::copy(m_string->cstr, m_string->cstr + m_string->length, str->cstr);
    std::copy(s.m_string->cstr, s.m_string->cstr + s.m_string->length, str->cstr + m_string->length);
    str->length = len;
    str->cstr[len] = '\0';
    reset();
    m_string = str;
    return *this;
}

ObjString operator+(const ObjString &s1, const ObjString &s2) {
    size_t len = s1.len() + s2.len();
    auto *result = new(len) FlatString();

    auto str1 = s1.m_string->cstr;
    auto len1 = s1.m_string->length;
    std::copy(str1, str1 + len1, result->cstr);

    auto str2 = s2.m_string->cstr;
    auto len2 = s2.m_string->length;
    std::copy(str2, str2 + len2, result->cstr + len1);
    result->cstr[len] = '\0';
    result->length = len;
    ObjString string{};
    string.m_string = result;
    return string;
}

bool operator==(const ObjString &lhs, const ObjString &rhs) {
    return strcmp(lhs.m_string->cstr, rhs.m_string->cstr) == 0;
}

bool operator==(const ObjString &lhs, const char *rhs) {
    return strcmp(lhs.m_string->cstr, rhs) == 0;
}

bool operator==(const char *lhs, const ObjString &rhs) {
    return strcmp(lhs, rhs.m_string->cstr) == 0;
}

bool operator!=(const ObjString &lhs, const ObjString &rhs) {
    return strcmp(lhs.m_string->cstr, rhs.m_string->cstr) != 0;
}

bool operator!=(const ObjString &lhs, const char *rhs) {
    return !(lhs == rhs);
}

bool operator!=(const char *lhs, const ObjString &rhs) {
    return !(lhs == rhs);
}

ObjString &ObjString::operator=(const char *s) {
    if (*this == s) {
        return *this;
    }
    reset();
    size_t length = strlen(s);
    m_string = new(length) FlatString();
    std::copy(s, s + length, m_string->cstr);
    m_string->cstr[length] = '\0';
    m_string->length = length;
    return *this;
}

size_t ObjString::len() const noexcept {
    return m_string->length;
}

char ObjString::operator[](size_t j) const noexcept {
    return m_string->cstr[j];
}

char &ObjString::operator[](size_t j) noexcept {
    return m_string->cstr[j];
}

ObjString ObjString::from(const std::string &string) {
    if (string.empty()) {
        return ObjString();
    }
    auto *str = new(string.length()) FlatString();
    std::copy(string.begin(), string.end(), str->cstr);
    str->length = string.length();
    str->cstr[str->length] = '\0';
    ObjString result{};
    result.m_string = str;
    return result;
}

void ObjString::reset() noexcept {
    delete m_string;
}

ObjString operator+(const char *s1, const ObjString &s2) {
    return ObjString(s1) + s2; //Todo rewrite it
}

ObjString operator+(const ObjString &s1, const char *s2) {
    return s1 + ObjString(s2); //Todo rewrite it to
}

const char *ObjString::cstr() const noexcept {
    return m_string->cstr;
}
