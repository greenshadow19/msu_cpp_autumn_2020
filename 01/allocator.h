//
// Created by kirill on 08.10.2020.
//

#ifndef MSU_CPP_AUTUMN_2020_ALLOCATOR_H
#define MSU_CPP_AUTUMN_2020_ALLOCATOR_H

class Allocator {
private:
    size_t maxSize;
    size_t currentSize;
    char *initialPosition;
    char *offset;
public:
    Allocator();

    void makeAllocator(size_t size);

    char *alloc(size_t size);

    void reset();

    ~Allocator();
};


#endif //MSU_CPP_AUTUMN_2020_ALLOCATOR_H
