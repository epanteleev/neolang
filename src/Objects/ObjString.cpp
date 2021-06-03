#include "Objects/ObjString.h"
#include "Vm/Allocator/DefaultAllocator.h"

#include <iostream>
#include <cstdint>
#include <cstring>

struct FlatString {
    size_t length;
    uint32_t hash;
    char cstr[0];

    inline void *operator new(size_t size, size_t length) {
        return (void *) DefaultAllocator::New(size + length + 1);
    }

    inline void operator delete(void *ptr) {
        DefaultAllocator::Delete(ptr);
    }

    static uint32_t jenkins_one_at_a_time_hash(const char *key, std::size_t len) {
        uint32_t hash, i;
        for(hash = i = 0; i < len; ++i)
        {
            hash += key[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash;
    }

    inline void calcHash() {
        hash = jenkins_one_at_a_time_hash(cstr, length);
    }
};

static FlatString* concat(const char* s1, size_t len1, const char* s2, size_t len2) {
    size_t len = len1 + len2;

    auto *result = new(len) FlatString();
    std::copy(s1, s1 + len1, result->cstr);
    std::copy(s2, s2 + len2, result->cstr + len1);
    result->cstr[len] = '\0';
    result->length = len;
    result->calcHash();
    return result;
}

ObjString::ObjString(const char *c) {
    if (c == nullptr) {
        UNREACHABLE();
    }
    size_t length = strlen(c);
    m_string = new(length) FlatString();
    m_string->length = length;
    std::copy(c, c + length, m_string->cstr);
    m_string->cstr[length] = '\0';
    m_string->calcHash();
}

ObjString::ObjString(const ObjString &s) {
    size_t length = s.len();
    m_string = new(length) FlatString();
    std::copy(s.m_string->cstr, s.m_string->cstr + s.m_string->length, m_string->cstr);
    m_string->length = length;
    m_string->cstr[length] = '\0';
    m_string->calcHash();
}


ObjString::~ObjString() {
    reset();
}

size_t ObjString::index(char c) const noexcept {
    for (size_t j = 0; j < m_string->length; j++) {
        if (m_string->cstr[j] == c) return j;
    }
    return std::numeric_limits<size_t>::max();
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
    m_string->calcHash();
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
    m_string->calcHash();
    return *this;
}

ObjString operator+(const ObjString &s1, const ObjString &s2) {
    return ObjString(concat(s1.cstr(), s1.len(), s2.cstr(), s2.len()));
}

bool operator==(const ObjString &lhs, const ObjString &rhs) {
    if (lhs.m_string->hash != rhs.m_string->hash) {
        return false;
    } else {
        return strcmp(lhs.m_string->cstr, rhs.m_string->cstr) == 0;
    }
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
    m_string->calcHash();
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
    std::copy(string.cbegin(), string.cend(), str->cstr);
    str->length = string.length();
    str->cstr[str->length] = '\0';
    ObjString result{};
    result.m_string = str;
    result.m_string->calcHash();
    return result;
}

void ObjString::reset() noexcept {
    if (m_string == nullptr) {
        return;
    }
    delete m_string;
}

ObjString operator+(const char *s1, const ObjString &s2) {
    return ObjString(concat(s1, strlen(s1), s2.cstr(), s2.len()));
}

ObjString operator+(const ObjString &s1, const char *s2) {
    return ObjString(concat(s1.cstr(), s1.len(), s2, strlen(s2)));
}

const char *ObjString::cstr() const noexcept {
    return m_string->cstr;
}