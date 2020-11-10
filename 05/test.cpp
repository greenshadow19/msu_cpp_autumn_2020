//
// Created by kirill on 08.11.2020.
//
#include <iostream>
#include <cassert>
#include "serializer.h"

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template<class Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b, c);
    }

    template<class Deserializer>
    Error deserialize(Deserializer &deserializer) {
        return deserializer(a, b, c);
    }

};

void taskDescriptionTest() {
    Data x{1, true, 2};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y{0, false, 0};

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void wrongFormatTest() {

    Data y = {1, true, 1};

    std::stringstream wrongAmountStream("1");
    std::stringstream negativeNumberStream("-5 false -5");
    std::stringstream notABooleanStream("5 not 5");

    Deserializer firstDeserializer(wrongAmountStream);
    Deserializer secondDeserializer(negativeNumberStream);
    Deserializer thirdDeserializer(notABooleanStream);

    assert(firstDeserializer.load(y) == Error::CorruptedArchive);
    assert(secondDeserializer.load(y) == Error::CorruptedArchive);
    assert(thirdDeserializer.load(y) == Error::CorruptedArchive);
}

int main() {
    taskDescriptionTest();
    wrongFormatTest();
    std::cout << "Success" << std::endl;
    return 0;
}
