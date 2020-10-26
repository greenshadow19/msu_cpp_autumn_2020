//
// Created by kirill on 26.10.2020.
//
#include <iostream>
#include <cassert>
#include <sstream>
#include "matrix.h"

void getterTest() {
    Matrix matrix(5, 3);
    size_t n = matrix.getNumberOfRows();
    size_t m = matrix.getNumberOfColumns();
    assert(n == 5);
    assert(m == 3);
}

void parenthesesTest() {
    Matrix matrix(5, 3);
    assert(matrix[1][0] == 0);
    matrix[1][0] = 5;
    assert(matrix[1][0] == 5);
}

void multiplyTest() {
    size_t numberOfRows = 5;
    size_t numberOfColumns = 3;
    Matrix matrix(numberOfRows, numberOfColumns);
    for (size_t i = 0; i < numberOfRows; i++) {
        for (size_t j = 0; j < numberOfColumns; j++) {
            matrix[i][j] = 1;
        }
    }
    matrix *= 19;
    Matrix correctAnswer(numberOfRows, 3);
    for (size_t i = 0; i < numberOfRows; ++i) {
        for (size_t j = 0; j < numberOfColumns; ++j) {
            correctAnswer[i][j] = 19;
        }
    }
    assert(matrix == correctAnswer);
}

void outstreamTest() {
    Matrix matrix(2, 2);
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    std::ostringstream output;
    output << matrix;
    std::string correctOutput =
            "1 0\n"
            "0 1\n";
    assert(output.str() == correctOutput);
}

void equalityTest() {
    Matrix matrix1(2, 2);
    Matrix matrix2(3, 2);
    Matrix matrix3(2, 2);
    Matrix matrix4(2, 2);
    matrix1[0][0] = 1;
    matrix1[1][1] = 1;
    matrix4[0][0] = 1;
    matrix4[1][1] = 1;
    assert(matrix1 != matrix2);
    assert(matrix1 != matrix3);
    assert(matrix1 == matrix4);
}

void additivityTest() {
    Matrix matrix1(2, 2);
    Matrix matrix2(2, 2);
    Matrix result(2, 2);
    Matrix correctResult(2, 2);
    for (size_t i = 0; i < correctResult.getNumberOfRows(); i++) {
        for (size_t j = 0; j < correctResult.getNumberOfColumns(); ++j) {
            correctResult[i][j] = 1;
        }
    }
    matrix1[0][0] = 1;
    matrix1[1][1] = 1;
    matrix2[0][1] = 1;
    matrix2[1][0] = 1;
    assert((matrix1 + matrix2) == correctResult);
}

int main() {
    getterTest();
    parenthesesTest();
    multiplyTest();
    outstreamTest();
    equalityTest();
    additivityTest();
    std::cout << "Success" << std::endl;
    return 0;
}
