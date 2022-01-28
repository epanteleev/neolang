#include <algorithm>

#include "Vm/Allocator/DefaultAllocator.h"
#include "Vm/Common.h"

void *DefaultAllocator::allocate(size_type size) {
    auto ptr = new type[size];
    m_pool.emplace_back(ptr);
    return ptr;
}

void DefaultAllocator::remove(void *ptr) {
    auto data = static_cast<pointer>(ptr);
    m_pool.remove(data);
    ::delete[] data;
}

static DefaultAllocator allocator;

void *Allocator::New(size_t size) {
    return allocator.allocate(size);
}

void Allocator::Delete(void *ptr) {
    allocator.remove(ptr);
}

void Allocator::setDefaultAllocator(Allocator *allocator) {
    UNREACHABLE();
}