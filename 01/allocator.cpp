#include <cstdio>
#include "allocator.h"

Allocator::Allocator() {
    maxSize = 0;
    currentSize = 0;
    initialPosition = nullptr;
    offset = nullptr;
}

void Allocator::makeAllocator(size_t size) {
    if (initialPosition != nullptr) {
        return;
    }
    maxSize = size;
    initialPosition = new char[maxSize];
    offset = initialPosition;
    currentSize = 0;
}

char *Allocator::alloc(size_t size) {
    if (size > maxSize - currentSize) {
        return nullptr;
    }
    offset = initialPosition + currentSize;
    currentSize += size;
    return offset;
}

void Allocator::reset() {
    offset = initialPosition;
    currentSize = 0;
}

Allocator::~Allocator() {
    if (initialPosition != nullptr) {
        delete[] initialPosition;
    }
}



