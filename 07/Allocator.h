#ifndef MSU_CPP_AUTUMN_2020_ALLOCATOR_H
#define MSU_CPP_AUTUMN_2020_ALLOCATOR_H

template<class T>
class Allocator {
public:
    T *allocate(size_t sizeOfAllocator) {
        T *pointerToT = (T *) calloc(sizeOfAllocator, sizeof(T));
        if (pointerToT == nullptr) {
            throw std::bad_alloc();
        }
        return pointerToT;
    }

    void deallocate(T *pointerToT, size_t sizeOfAllocator) {
        free(pointerToT);
    }

    size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    void construct(T *pointerToT, const T &value, size_t sizeOfAllocator) {
        for (size_t i = 0; i < sizeOfAllocator; i++) {
            new(pointerToT + i) T(value);
        }
    }

    void construct(T *pointerToT, size_t sizeOfAllocator) {
        for (size_t i = 0; i < sizeOfAllocator; i++) {
            new(pointerToT + i) T();
        }
    }

    void destroy(T *pointerToT, size_t sizeOfAllocator) {
        for (size_t i = 0; i < sizeOfAllocator; i++) {
            (pointerToT[i]).~T();
        }
    }
};

#endif //MSU_CPP_AUTUMN_2020_ALLOCATOR_H