#include <algorithm>

#include "Vm/Allocator/DefaultAllocator.h"
#include "Vm/Common.h"

void *DefaultAllocator::allocate(size_t size) {
    return new uint8_t[size];
}

void DefaultAllocator::remove(void *ptr) {
    ::delete[] reinterpret_cast<uint8_t *>(ptr);
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
