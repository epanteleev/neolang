#pragma once

#include <list>
#include <cstdint>

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
    DefaultAllocator() = default;

    ~DefaultAllocator() = default;

    DefaultAllocator(DefaultAllocator &) = delete;

public:
    void *allocate(size_t size) override;

    void remove(void *ptr) override;
};
