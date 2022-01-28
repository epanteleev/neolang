#pragma once

#include <set>
#include <cstdint>
#include <Vm/Common.h>

class Allocator {
public:
    static void *New(size_t size);

    static void Delete(void *ptr);

    static void setDefaultAllocator(Allocator* allocator);

public:
    virtual void *allocate(size_t size) = 0;

    virtual void remove(void *ptr) = 0;

};

class DefaultAllocator : public Allocator {
public:
    using type = std::uint8_t;
    using pointer = type *;
    using holder = std::set<pointer>;
    using size_type = std::size_t;

public:
    DefaultAllocator() = default;

    ~DefaultAllocator() = default;

    DefaultAllocator(DefaultAllocator &) = delete;

public:
    void *allocate(size_type size) override;

    void remove(void *ptr) override;

    /**
     * @return current allocated memory size.
     */
    size_type allocated_size() const {
        ASSERT(false, "unimplemented yet");
    }

    size_type size() const {
        ASSERT(false, "unimplemented yet");
    }
private:
    holder m_pool{};
};
