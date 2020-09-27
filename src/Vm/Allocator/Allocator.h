#pragma once

#include <list>
#include <cstdint>

class Allocator final {
public:
    Allocator() = default;

    ~Allocator() = default;

    Allocator(Allocator &) = delete;

public:
    static void* New(size_t size);

    static void Delete (void* ptr);

public:
    void* allocate(size_t size) noexcept;

    void remove(void* ptr) noexcept;
};