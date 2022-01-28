#pragma once

#include <iostream> //todo
#include "Vm/Common.h"
#include "cassert"

class Buffer {
public:
    using size_type = std::size_t;
    using data_type = char;
    using pointer = data_type *;
    using const_pointer = const data_type *;
    using reference = data_type &;

public:
    Buffer() = default;

    explicit Buffer(size_type cap) :
            m_capacity(cap),
            m_size(0),
            m_p(reinterpret_cast<pointer>(std::malloc(cap))) {
    }

    Buffer(void *p, size_type size, size_type cap) noexcept:
        m_capacity(cap),
        m_size(size),
        m_p(reinterpret_cast<pointer>(p))
        {}

    ~Buffer() {
        reset();
    }

    Buffer(const Buffer &) = delete;

    Buffer(Buffer &&s) noexcept:
            m_capacity(std::exchange(s.m_capacity, 0)),
            m_size(std::exchange(s.m_size, 0)),
            m_p(std::exchange(s.m_p, nullptr))
            {}

public:

    Buffer operator=(const Buffer &) = delete;

    Buffer &operator=(Buffer &&s) noexcept {
        if (&s != this) {
            if (m_p) free(m_p);
            new(this) Buffer(std::move(s));
        }
        return *this;
    }

public:
    [[nodiscard]]
    pointer data() const {
        return m_p;
    }

    [[nodiscard]]
    inline size_type size() const {
        return m_size;
    }

    [[nodiscard]]
    inline bool empty() const {
        return m_size == 0;
    }

    [[nodiscard]]
    inline size_type capacity() const {
        return m_capacity;
    }

    inline void clear() {
        m_size = 0;
    }

    void resize(size_type n) {
        reserve(n);
        m_size = n;
    }

    void reserve(size_type n) {
        if (m_capacity < n) {
            m_p = reinterpret_cast<pointer>(std::realloc(m_p, n));
            ASSERT(m_p, "expect not null");
            m_capacity = n;
        }
    }

    void reset() {
        std::free(m_p);
        m_capacity = m_size = 0;
    }

    void ensure(size_type n) {
        if (m_capacity >= m_size + n) {
            return;
        }
        m_capacity += ((m_capacity >> 1) + n);
        m_p = reinterpret_cast<pointer>(std::realloc(m_p, m_capacity));
        ASSERT(m_p, "not null");
    }

    [[nodiscard]]
    const_pointer c_str() {
        reserve(m_size + 1);
        if (m_p[m_size] != '\0') {
            m_p[m_size] = '\0';
        }
        return m_p;
    }

    [[nodiscard]]
    reference back() const {
        return m_p[m_size - 1];
    }

    [[nodiscard]]
    reference front() const {
        return m_p[0];
    }

    reference operator[](size_type i) const {
        return m_p[i];
    }

public:

    Buffer &append(data_type c) {
        ensure(1);
        m_p[m_size++] = c;
        return *this;
    }

    Buffer &append(const_pointer p, size_type n) {
        ensure(n);
        std::memcpy(m_p + m_size, p, n);
        m_size += n;
        return *this;
    }

    template<typename ... Args>
    Buffer & vprint(const char* format, Args ... args) {
        auto size = std::snprintf(nullptr, 0, format, args ...);
        ensure(size);
        std::snprintf(m_p + m_size, size, format, args ...);
        m_size += size;
        return *this;
    }

private:
    size_type m_capacity{};
    size_type m_size{};
    pointer m_p{};
};