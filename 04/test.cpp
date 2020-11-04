//
// Created by kirill on 01.11.2020.
//
#include <iostream>
#include <cassert>
#include "BigInt.h"

void intConstructorTest() {
    BigInt bigIntegerFromInt = BigInt(10150015);
    size_t sizeOfNumbers = bigIntegerFromInt.getSize();
    uint *numbers = bigIntegerFromInt.getNumbers();
    bool isNegative = bigIntegerFromInt.getIsNegative();
    assert(sizeOfNumbers == 2);
    assert(numbers[0] == 15);
    assert(numbers[1] == 1015);
    assert(isNegative == false);
}

void stringConstructorTest() {
    BigInt a("123456789012345678901234567890");
    BigInt b("10");
    BigInt c("-123456789012345678901234567890");
    uint A[8] = {7890, 3456, 9012, 5678, 1234, 7890, 3456, 12};
    uint B[1] = {10};
    size_t size = a.getSize();
    uint *copy = a.getNumbers();

    assert(!a.getIsNegative());
    for (size_t i = 0; i < size; i++) {
        assert(copy[i] == A[i]);
    }

    size = b.getSize();
    copy = b.getNumbers();

    assert(!b.getIsNegative());
    for (size_t i = 0; i < size; i++) {
        assert(copy[i] == B[i]);
    }
    size = c.getSize();
    copy = c.getNumbers();

    assert(c.getIsNegative());
    for (size_t i = 0; i < size; i++) {
        assert(copy[i] == A[i]);
    }
}

void moveTest() {
    BigInt a("132432078458712346973421");
    a = a;
    BigInt moveA = std::move(a);
    assert(moveA == BigInt("132432078458712346973421"));
}

void comparatorTest() {
    BigInt smaller("12345678901234567801234567890");
    BigInt larger("123456789012345678012345678901234567801234567890");
    BigInt equal("12345678901234567801234567890");
    BigInt largerButALittleBit("12345678901234567801234567891");


    assert(smaller < larger);
    assert(smaller <= larger);
    assert(larger > smaller);
    assert(larger >= smaller);
    assert(smaller < largerButALittleBit);
    assert(smaller == equal);
    assert(smaller != largerButALittleBit);

    BigInt negativeSmaller("-12345678901234567801234567890");
    BigInt negativelargerButALittleBit("-12345678901234567801234567891");
    assert(negativeSmaller < 1);
    assert(negativeSmaller > negativelargerButALittleBit);
    assert(negativeSmaller >= negativelargerButALittleBit);
    assert(negativeSmaller != smaller);
}

void outputTest() {
    BigInt someBigNumber("12345678901234567801234567890");
    BigInt anotherBigNumber("-12345678901234567801234567890");
    std::ostringstream output;
    output << someBigNumber;

    assert(output.str() == "12345678901234567801234567890");

    output.str("");
    output.clear();
    output << anotherBigNumber;
    assert(output.str() == "-12345678901234567801234567890");
}

void unaryMinusTest() {
    BigInt someBigNumber("12345678901234567801234567890");
    BigInt negativeSomeBigNumber = -someBigNumber;
    assert(negativeSomeBigNumber == BigInt("-12345678901234567801234567890"));
}

void arithmeticOperationTest() {
    BigInt a("123456789012345678901234567890");
    BigInt b("987654321098765432109876543210");
    BigInt negativeA = -a;
    BigInt negativeB = -b;

    BigInt addition = a + b;
    BigInt subtraction = a - b;
    BigInt anotherSubtraction = b - a;
    BigInt negativeSubtraction = negativeA - negativeB;
    BigInt distributiveness = -(a + b);

    BigInt additionWithInt = a + 5;
    BigInt subtractionWithInt = a - 5;


    assert(addition == BigInt("1111111110111111111011111111100"));
    assert(subtraction == BigInt("-864197532086419753208641975320"));
    assert(anotherSubtraction == -subtraction);
    assert(negativeSubtraction == anotherSubtraction);
    assert(distributiveness == -addition);
    assert(additionWithInt == BigInt("123456789012345678901234567895"));
    assert(subtractionWithInt == BigInt("123456789012345678901234567885"));
}

void multiplicationTest() {

    BigInt a("123456789012345678901234567890");
    BigInt b("987654321098765432109876543210");

    BigInt c = a * b;
    BigInt multipliedByInt = 5 * a;
    BigInt multipliedByNegative = (-a) * b;
    BigInt twoNegatives = (-a) * (-b);

    assert(c == BigInt("121932631137021795226185032733622923332237463801111263526900"));
    assert(multipliedByInt == BigInt("617283945061728394506172839450"));
    assert(multipliedByNegative == -c);
    assert(twoNegatives == c);
}

int main() {
    intConstructorTest();
    stringConstructorTest();
    moveTest();
    comparatorTest();
    outputTest();
    unaryMinusTest();
    arithmeticOperationTest();
    multiplicationTest();
    std::cout << "Success" << std::endl;
    return 0;
}
