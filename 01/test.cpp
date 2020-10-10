//
// Created by kirill on 08.10.2020.
//
#include <iostream>
#include "allocator.h"

int main() {
    try {
        Allocator *allocator = new Allocator();

        allocator->makeAllocator(10);

        char *memory_1 = allocator->alloc(5);
        std::cout << "Some memory is allocated on " <<
                  std::hex << &memory_1 << std::endl;
        if (memory_1 == nullptr) {
            throw "FAIL";
        }
        char *memory_2 = allocator->alloc(5);
        std::cout << "Some memory is allocated on " <<
                  std::hex << &memory_2 << std::endl;
        if (memory_2 == nullptr || memory_2 == memory_1) {
            throw "FAIL";
        }
        memory_1 = allocator->alloc(5);
        if (memory_1 != nullptr) {
            throw "FAIL";
        }
        allocator->reset();
        memory_1 = allocator->alloc(5);
        if (memory_1 == nullptr) {
            throw "FAIL";
        }
        std::cout << "SUCCESS" << std::endl;
    } catch (const char *error) {
        std::cout << error << std::endl;
    }
    return 0;
}
