#ifndef MSU_CPP_AUTUMN_2020_ITERATOR_H
#define MSU_CPP_AUTUMN_2020_ITERATOR_H

template<class T>
class Iterator {
private:
    T *pointerToT;
    bool isReverse;
public:
    explicit Iterator(T *ptr, bool reverse) : pointerToT(ptr), isReverse(reverse) {}

    bool operator==(const Iterator<T> &other) const {
        return pointerToT == other.pointerToT;
    }

    bool operator!=(const Iterator<T> &other) const {
        return pointerToT != other.pointerToT;
    }

    T &operator*() const {
        return *pointerToT;
    }

    Iterator &operator++() {
        if (isReverse) {
            --pointerToT;
        } else {
            ++pointerToT;
        }
        return *this;
    }

    Iterator operator++(int) {
        Iterator it(pointerToT, isReverse);
        if (isReverse) {
            --pointerToT;
        } else {
            ++pointerToT;
        }
        return it;
    }

    Iterator &operator--() {
        if (isReverse) {
            ++pointerToT;
        } else {
            --pointerToT;
        }
        return *this;
    }

    Iterator operator--(int) {
        Iterator it(pointerToT, isReverse);
        if (isReverse) {
            ++pointerToT;
        } else {
            --pointerToT;
        }
        return it;
    }

    Iterator &operator+(size_t n) {
        if (isReverse) {
            pointerToT -= n;
        } else {
            pointerToT += n;
        }
        return *this;
    }

    Iterator &operator-(size_t n) {
        if (isReverse) {
            pointerToT += n;
        } else {
            pointerToT -= n;
        }
        return *this;
    }
};

#endif //MSU_CPP_AUTUMN_2020_ITERATOR_H
