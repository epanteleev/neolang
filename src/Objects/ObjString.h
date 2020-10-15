#pragma once

#include <iosfwd>
#include <cstdint>
#include <Vm/Value.h>
#include <utility>

class FlatString;

/**
 * Represent string class as flat structure wrapper.
 * @author minium2
 */
class ObjString {
public:
    ObjString() = default;

    ObjString(const char *c);

    ObjString(const ObjString &s);

    ObjString(ObjString &&s) noexcept:
            m_string(std::exchange(s.m_string, nullptr)) {}

    ObjString &operator=(ObjString &&s) noexcept {
        m_string = std::exchange(s.m_string, nullptr);
        return *this;
    }

    virtual ~ObjString();

private:
    explicit ObjString(FlatString *flatString)
        : m_string(flatString) {}

public:

    [[nodiscard]]
    size_t len() const noexcept;

    [[nodiscard]]
    size_t index(char c) const noexcept;

    [[nodiscard]]
    const char *cstr() const noexcept;

    friend std::ostream &operator<<(std::ostream &so, const ObjString &s);

    char operator[](size_t j) const noexcept;

    char &operator[](size_t j) noexcept;

    ObjString &operator=(const ObjString &s);

    ObjString &operator=(const char *s);

    ObjString &operator+=(const ObjString &s);

public:

    friend ObjString operator+(const ObjString &s1, const ObjString &s2);

    friend ObjString operator+(const char *s1, const ObjString &s2);

    friend ObjString operator+(const char *s1, const ObjString &s2);

    friend ObjString operator+(const ObjString &s1, const char *s2);

    friend bool operator==(const ObjString &lhs, const ObjString &rhs);

    friend bool operator==(const ObjString &lhs, const char *rhs);

    friend bool operator==(const char *lhs, const ObjString &rhs);

    friend bool operator!=(const ObjString &lhs, const ObjString &rhs);

    friend bool operator!=(const ObjString &lhs, const char *rhs);

    friend bool operator!=(const char *lhs, const ObjString &rhs);

public:
    [[nodiscard]]
    inline Value value() const noexcept {
        return Value((uintptr_t) m_string);
    }

    [[nodiscard]]
    inline Value toValueAndRelease() noexcept {
        return Value((uintptr_t) std::exchange(m_string, nullptr));
    }

public:
    static ObjString from(const std::string &string);

private:
    void reset() noexcept;

protected:
    FlatString *m_string{};
};


class ObjStringViewer : public ObjString {
public:
    explicit ObjStringViewer(Value value) {
        m_string = reinterpret_cast<FlatString *>(value.value());
    }

    ~ObjStringViewer() override {
        m_string = nullptr;
    }
};