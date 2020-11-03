//
// Created by kirill on 01.11.2020.
//

#ifndef MSU_CPP_AUTUMN_2020_BIGINT_H
#define MSU_CPP_AUTUMN_2020_BIGINT_H

#include <cstdio>
#include <string>
#include <ostream>
#include <iomanip>

class BigInt {
private:
    uint *numbers;
    size_t sizeOfNumbers;
    bool isNegative;

    static const uint BASE = 10000;
    static const int NUMDIG = 4;

    BigInt addWithoutSign(const BigInt &bigNum) const;

    // suppose that subtracts the smaller from the larger
    BigInt subWithoutSign(const BigInt &bigNum) const;

    int comparator(const BigInt &bigNum) const;

    BigInt multiplication(const BigInt &bigNum) const;

public:
    BigInt();

    BigInt(int num);

    BigInt(const BigInt &bigNumber);

    BigInt(BigInt &&bigNumber);

    BigInt(std::string stringNumber);

    ~BigInt();

    BigInt operator=(const BigInt &bigNum);

    BigInt operator=(BigInt &&bigNum);

    uint *getNumbers() const;

    size_t getSize() const;

    bool getIsNegative() const {
        return isNegative;
    }

    BigInt operator-() const;

    friend BigInt operator+(const BigInt &leftBig, const BigInt &rightBig);

    friend BigInt operator-(const BigInt &leftBig, const BigInt &rightBig);

    friend bool operator<(const BigInt &leftBig, const BigInt &rightBig);

    friend bool operator>(const BigInt &leftBig, const BigInt &rightBig);

    friend bool operator<=(const BigInt &leftBig, const BigInt &rightBig);

    friend bool operator>=(const BigInt &leftBig, const BigInt &rightBig);

    friend bool operator==(const BigInt &leftBig, const BigInt &rightBig);

    friend bool operator!=(const BigInt &leftBig, const BigInt &rightBig);

    friend std::ostream &operator<<(std::ostream &out, const BigInt &bigNum);

    friend BigInt operator*(const BigInt &leftBig, const BigInt &rightBig);
};


#endif //MSU_CPP_AUTUMN_2020_BIGINT_H
