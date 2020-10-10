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

        // check if memory is allocated
        if (memory_1 == nullptr) {
            throw "memory is not allocated";
        }
        char *memory_2 = allocator->alloc(5);
        std::cout << "Some memory is allocated on " <<
                  std::hex << &memory_2 << std::endl;

        // check if memory is allocated on another adress
        if (memory_2 == nullptr || memory_2 == memory_1) {
            if (memory_2 == nullptr) {
	    	throw "memory is not allocated";
	    } else {
		throw "memory is allocated on the same address";
	    }
        }
        memory_1 = allocator->alloc(5);

        // check oversize allocation
        if (memory_1 != nullptr) {
            throw "memory is allocated in oversize zone";
        }
        allocator->reset();
        memory_1 = allocator->alloc(5);

        // check reset
        if (memory_1 == nullptr) {
            throw "reset has note been done";
        }

        allocator->reset();

        allocator->makeAllocator(15);

        char *memory_3 = allocator->alloc(12);

        // check that we can't reallocate before reset
        if (memory_3 != nullptr) {
            throw "reallocacation is made before reset";
        }

        std::cout << "SUCCESS" << std::endl;

	delete allocator;
    } catch (const char *error) {
        std::cout << error << std::endl;
    }
    return 0;
}
