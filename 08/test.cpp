//
// Created by kirill on 10.12.2020.
//
#include <iostream>
#include <cassert>
#include "ThreadPool.h"

struct A {
    int field;
};

int getField(const A& aObject) {return aObject.field;}

void simpleFunctionTest() {
    int x = 5;
    int y = 3;
    ThreadPool pool(2);
    auto firstTask = pool.exec([](int x, int y) {return x + y;}, x, y);
    auto secondTask = pool.exec([](int x){return 1 << x;}, x);
    int firstResult = firstTask.get();
    int secondResult = secondTask.get();
    assert(firstResult == 8);
    assert(secondResult == 32);
}

void structTest() {
    ThreadPool pool(1);

    auto task = pool.exec(getField, A{5});
    int fieldOfA = task.get();
    assert(fieldOfA == 5);
}

int main() {
    simpleFunctionTest();
    structTest();
    std::cout << "Success" << std::endl;
    return 0;
}