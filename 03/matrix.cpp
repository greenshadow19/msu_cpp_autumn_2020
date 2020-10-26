//
// Created by kirill on 26.10.2020.
//

#include <cstdio>
#include <stdexcept>
#include <sstream>
#include "matrix.h"


Matrix::Row::Row() {};

Matrix::Row::Row(size_t numberOfColumns) {
    this->numberOfColumns = numberOfColumns;
    this->numbers = std::vector<int>(numberOfColumns);
}

int &Matrix::Row::operator[](size_t column) {
    if (column >= numberOfColumns) {
        throw std::out_of_range("columns index out of range");
    }
    return numbers[column];
}

const int &Matrix::Row::operator[](size_t column) const {
    if (column >= numberOfColumns) {
        throw std::out_of_range("columns index out of range");
    }
    return numbers[column];
}


Matrix::Matrix(size_t numberOfRows, size_t numberOfColumns) {
    this->numberOfColumns = numberOfColumns;
    this->numberOfRows = numberOfRows;

    rows = std::vector<Row>(numberOfRows);
    for (auto &row : rows) {
        row = Row(numberOfColumns);
    }
}

Matrix::Row &Matrix::operator[](size_t row) {
    if (row >= numberOfRows) {
        throw std::out_of_range("rows index out of range");
    }
    return rows[row];
}

const Matrix::Row &Matrix::operator[](size_t row) const {
    if (row >= numberOfRows) {
        throw std::out_of_range("rows index out of range");
    }
    return rows[row];
}

size_t Matrix::getNumberOfColumns() const {
    return numberOfColumns;
}

size_t Matrix::getNumberOfRows() const {
    return numberOfRows;
}

Matrix &Matrix::operator*=(int number) {
    for (size_t i = 0; i < numberOfRows; i++) {
        for (size_t j = 0; j < numberOfColumns; j++) {
            (*this)[i][j] *= number;
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix &matrix) const {
    if (matrix.getNumberOfColumns() != this->getNumberOfColumns() ||
        matrix.getNumberOfRows() != this->getNumberOfRows()) {
        return false;
    }

    for (size_t i = 0; i < matrix.getNumberOfRows(); i++) {
        for (size_t j = 0; j < matrix.getNumberOfColumns(); j++) {
            if (matrix[i][j] != (*this)[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &matrix) const {
    return !(*this == matrix);
}


std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    size_t numberOfRows = matrix.getNumberOfRows();
    size_t numberOfColumns = matrix.getNumberOfColumns();
    for (size_t i = 0; i < numberOfRows; i++) {
        for (size_t j = 0; j < numberOfColumns; j++) {
            os << matrix[i][j];
            if (j < numberOfColumns - 1) {
                os << " ";
            }
        }
        os << "\n";
    }
    return os;
}

Matrix operator+(const Matrix &leftMatrix, const Matrix &rightMatrix) {
    if (leftMatrix.getNumberOfColumns() != rightMatrix.getNumberOfColumns() ||
        leftMatrix.getNumberOfRows() != rightMatrix.getNumberOfRows()) {
        throw std::out_of_range("Sizes of matrices are different");
    }
    size_t numberOfRows = leftMatrix.getNumberOfRows();
    size_t numberOfColumns = leftMatrix.getNumberOfColumns();
    Matrix result(numberOfRows, numberOfColumns);
    for (size_t i = 0; i < numberOfRows; ++i) {
        for (size_t j = 0; j < numberOfColumns; ++j) {
            result[i][j] = leftMatrix[i][j] + rightMatrix[i][j];
        }
    }
    return result;
}
