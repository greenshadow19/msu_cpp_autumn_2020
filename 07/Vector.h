#ifndef MSU_CPP_AUTUMN_2020_VECTOR_H
#define MSU_CPP_AUTUMN_2020_VECTOR_H

#include <limits>
#include "Allocator.h"
#include "Iterator.h"



template<class T, class AllocT = Allocator<T> >
class Vector {
    size_t sizeOfVector;
    size_t capacityOfVector;
    AllocT allocator;
    T *data;
public:

    explicit Vector() : sizeOfVector(0), capacityOfVector(0), data(nullptr) {}

    explicit Vector(size_t aSizeOfVector) : sizeOfVector(aSizeOfVector), capacityOfVector(aSizeOfVector) {
        data = allocator.allocate(aSizeOfVector);
        allocator.construct(data, aSizeOfVector);
    }

    Vector(size_t aSizeOfVector, const T &value) : sizeOfVector(aSizeOfVector), capacityOfVector(aSizeOfVector) {
        data = allocator.allocate(aSizeOfVector);
        allocator.construct(data, value, aSizeOfVector);
    }

    Vector(const Vector<T> &vector) : sizeOfVector(vector.size()), capacityOfVector(vector.capacity()) {
        data = allocator.allocate(this->sizeOfVector);
        for (size_t i = 0; i < vector.size(); i++) {
            data[i] = vector[i];
        }
    }

    Vector(const Vector<T> &&otherVector) : sizeOfVector(otherVector.size()), capacityOfVector(otherVector.capacity()) {
        data = allocator.allocate(this->sizeOfVector);
        for (size_t i = 0; i < otherVector.size(); i++) {
            data[i] = otherVector[i];
        }
        allocator.destroy(otherVector.data, sizeOfVector);
        allocator.deallocate(otherVector.data, capacityOfVector);
    }

    ~Vector() {
        allocator.destroy(data, sizeOfVector);
        allocator.deallocate(data, capacityOfVector);
    }

    Iterator<T> begin() noexcept {
        return Iterator<T>(data, false);
    }

    Iterator<T> end() noexcept {
        return Iterator<T>(data + sizeOfVector, false);
    }

    Iterator<T> rbegin() noexcept {
        return Iterator<T>(data + sizeOfVector - 1, true);
    }

    Iterator<T> rend() noexcept {
        return Iterator<T>(data - 1, true);
    }

    void push_back(T &&value) {
        resize(sizeOfVector + 1, value);
        data[sizeOfVector - 1] = std::move(value);
    }

    void push_back(const T &value) {
        resize(sizeOfVector + 1, value);
        data[sizeOfVector - 1] = std::move(value);
    }

    void pop_back() {
        if (sizeOfVector > 0)
            allocator.destroy(data + (--sizeOfVector), 1);
    }

    void reserve(size_t sizeToReserve) {
        if (sizeToReserve > allocator.max_size())
            throw std::length_error("Can't reserve this much elements");
        if (sizeToReserve <= capacityOfVector)
            return;

        T *newData = allocator.allocate(sizeToReserve);
        for (size_t i = 0; i < sizeOfVector; ++i)
            newData[i] = std::move(data[i]);
        allocator.destroy(data, sizeOfVector);
        allocator.deallocate(data, capacityOfVector);
        data = newData;
        capacityOfVector = sizeToReserve;
    }

    void resize(size_t newSizeOfVector, const T &val) {
        if (newSizeOfVector == sizeOfVector) return;
        if (newSizeOfVector < sizeOfVector) {
            allocator.destroy(data + newSizeOfVector, sizeOfVector - newSizeOfVector);
            sizeOfVector = newSizeOfVector;
            return;
        }

        if (newSizeOfVector > capacityOfVector)
            reserve(newSizeOfVector > 2 * capacityOfVector ? newSizeOfVector : 2 * capacityOfVector);
        allocator.construct(data + sizeOfVector, val, newSizeOfVector - sizeOfVector);
        sizeOfVector = newSizeOfVector;
    }

    void resize(size_t newSizeOfVector) {
        if (newSizeOfVector == sizeOfVector) return;
        if (newSizeOfVector < sizeOfVector) {
            allocator.destroy(data + newSizeOfVector, sizeOfVector - newSizeOfVector);
            sizeOfVector = newSizeOfVector;
            return;
        }

        if (newSizeOfVector > capacityOfVector)
            reserve(newSizeOfVector > 2 * capacityOfVector ? newSizeOfVector : 2 * capacityOfVector);
        allocator.construct(data + sizeOfVector, newSizeOfVector - sizeOfVector);
        sizeOfVector = newSizeOfVector;
    }

    template<typename... ArgsT>
    void emplace_back(ArgsT&&... args) {
        if (sizeOfVector==capacityOfVector) {
            resize(sizeOfVector + 1);
        }
        data[sizeOfVector-1] = T(args...);
    }

    void clear() noexcept {
        allocator.destroy(data, sizeOfVector);
        sizeOfVector = 0;
    }

    Vector &operator=(const Vector<T> &otherVector) {
        if (otherVector == (*this)) {
            return *this;
        }
        this->sizeOfVector = otherVector.size();
        this->capacityOfVector = otherVector.capacity();
        this->data = allocator.allocate(sizeOfVector);
        for (size_t i = 0; i < sizeOfVector; i++) {
            this->data[i] = otherVector[i];
        }
        return *this;
    }

    Vector &operator=(Vector<T> &&otherVector) {
        if (otherVector == (*this)) {
            return *this;
        }
        this->sizeOfVector = otherVector.size();
        this->capacityOfVector = otherVector.capacity();
        this->data = allocator.allocate(sizeOfVector);
        for (size_t i = 0; i < sizeOfVector; i++) {
            this->data[i] = otherVector[i];
        }

        allocator.destroy(otherVector.data, sizeOfVector);
        allocator.deallocate(otherVector.data, capacityOfVector);

        return *this;
    }

    T &operator[](size_t i) {
        return data[i];
    }

    const T &operator[](size_t i) const {
        return data[i];
    }

    bool empty() const noexcept {
        return sizeOfVector == 0;
    }

    size_t size() const noexcept {
        return sizeOfVector;
    }

    size_t capacity() const noexcept {
        return capacityOfVector;
    }
};

#endif //MSU_CPP_AUTUMN_2020_VECTOR_H