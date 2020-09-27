#include <algorithm>

#include "Vm/Allocator/Allocator.h"

void* Allocator::allocate(size_t size) noexcept {
    auto *ptr = new uint8_t[size];
    return ptr;
}

void Allocator::remove(void* ptr) noexcept {
    ::delete[] ptr;
}

static Allocator _allocator;

void *Allocator::New(size_t size) {
    return _allocator.allocate(size);
}

void Allocator::Delete(void *ptr) {
    _allocator.remove(ptr);
}