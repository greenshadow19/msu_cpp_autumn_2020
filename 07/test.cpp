#include <iostream>
#include <cassert>
#include "Vector.h"

void pushPopTest() {
    Vector<int> vectorOfInt;
    vectorOfInt.push_back(9);
    assert(vectorOfInt.size() == 1);
    vectorOfInt.pop_back();
    assert(vectorOfInt.size() == 0);
}

void emptyClearTest() {
    Vector<int> vectorOfInt;
    assert(vectorOfInt.empty());

    vectorOfInt.push_back(9);
    vectorOfInt.clear();
    assert(vectorOfInt.empty());
}

void stringVectorTest() {
    Vector<std::string> vectorOfString;
    std::string hello = "Hello, World!";
    vectorOfString.push_back(hello);
    assert(vectorOfString[0] == "Hello, World!");
}

void iteratorTest() {
    Vector<int> vectorOfInt;
    for (int i = 0; i < 9; i++) {
        vectorOfInt.push_back(i);
    }
    int count = 0;
    for (auto iter = vectorOfInt.begin(); iter != vectorOfInt.end(); iter++) {
        assert(*iter == (count++));
    }
}

void emplaceBackTest() {
    Vector<int> vectorOfInt;
    vectorOfInt.emplace_back(9);
    assert(vectorOfInt[0] == 9);
}

int main() {
    pushPopTest();
    emptyClearTest();
    stringVectorTest();
    iteratorTest();
    emplaceBackTest();
    std::cout << "Success" << std::endl;
    return 0;
}