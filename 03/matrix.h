//
// Created by kirill on 26.10.2020.
//

#ifndef MSU_CPP_AUTUMN_2020_MATRIX_H
#define MSU_CPP_AUTUMN_2020_MATRIX_H

class Matrix {
private:

    size_t numberOfColumns;
    size_t numberOfRows;

    class Row {
    private:
        size_t numberOfColumns;
        int *numbers;
    public:
        Row();

        Row(size_t numberOfColumns);

        ~Row();

        int &operator[](size_t column);

        const int &operator[](size_t column) const;
    };

    int **rows;

public:
    Matrix(size_t numberOfRows, size_t numberOfColumns);

    ~Matrix();

    int *operator[](size_t row);

    const int *operator[](size_t row) const;

    size_t getNumberOfRows() const;

    size_t getNumberOfColumns() const;

    Matrix &operator*=(int number);

    bool operator==(const Matrix &matrix) const;

    bool operator!=(const Matrix &matrix) const;
};


Matrix operator+(const Matrix &leftMatrix, const Matrix &rightMatrix);

std::ostream &operator<<(std::ostream &os, const Matrix &matrix);


#endif //MSU_CPP_AUTUMN_2020_MATRIX_H
