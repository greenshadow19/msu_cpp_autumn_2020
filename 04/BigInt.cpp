//
// Created by kirill on 01.11.2020.
//
#include "BigInt.h"

BigInt::BigInt() : numbers(nullptr), sizeOfNumbers(0), isNegative(false) {}

BigInt::BigInt(int num) {
    int copyNum = num;
    sizeOfNumbers = 0;
    while (copyNum >= 1) {
        sizeOfNumbers++;
        copyNum /= BASE;
    }
    isNegative = (num < 0);
    numbers = new uint[sizeOfNumbers];
    num = isNegative ? -num : num;
    for (int i = 0; i < sizeOfNumbers; i++) {
        numbers[i] = num % BASE;
        num /= BASE;
    }
};

BigInt::BigInt(const BigInt &bigNumber) : sizeOfNumbers(bigNumber.sizeOfNumbers), isNegative(bigNumber.isNegative) {
    numbers = new uint[sizeOfNumbers];
    for (int i = 0; i < sizeOfNumbers; i++) {
        numbers[i] = bigNumber.numbers[i];
    }
}

BigInt::BigInt(BigInt &&bigNumber) : numbers(bigNumber.numbers), sizeOfNumbers(bigNumber.sizeOfNumbers),
                                     isNegative(bigNumber.isNegative) {
    bigNumber.sizeOfNumbers = 0;
    bigNumber.numbers = nullptr;
}

BigInt::BigInt(const std::string &stringNumber) {
    int initialPosition = 0;
    if (stringNumber[0] == '-') {
        initialPosition++;
        isNegative = true;
    } else {
        isNegative = false;
    }

    sizeOfNumbers = (stringNumber.size() + NUMDIG - 1) / NUMDIG;
    numbers = new uint[sizeOfNumbers];

    int begin = stringNumber.size() - NUMDIG;
    int numbefOfDigits = NUMDIG;
    for (int i = 0; i < sizeOfNumbers; i++) {
        if (begin < initialPosition) {
            numbefOfDigits = begin + NUMDIG;
            if (isNegative) {
                numbefOfDigits--;
            }
            begin = initialPosition;
        }
        std::string substr = stringNumber.substr(begin, numbefOfDigits);
        uint tempNum = std::stoull(substr);
        numbers[i] = tempNum;
        begin -= NUMDIG;
    }
}

BigInt::~BigInt() {
    if (sizeOfNumbers > 0) {
        sizeOfNumbers = 0;
        delete[] numbers;
    }
}

BigInt &BigInt::operator=(const BigInt &bigNum) {

    if (bigNum == *this) {
        return *this;
    }

    if (numbers != nullptr) {
        delete[] numbers;
    }

    sizeOfNumbers = bigNum.sizeOfNumbers;
    isNegative = bigNum.isNegative;

    numbers = new uint[sizeOfNumbers];
    for (size_t i = 0; i < sizeOfNumbers; ++i) {
        numbers[i] = bigNum.numbers[i];
    }
    return (*this);
}

BigInt &BigInt::operator=(BigInt &&bigNum) {

    if (numbers!= nullptr) {
        delete[] numbers;
    }

    sizeOfNumbers = bigNum.sizeOfNumbers;
    isNegative = bigNum.isNegative;
    numbers = bigNum.numbers;

    bigNum.sizeOfNumbers = 0;
    bigNum.numbers = nullptr;

    return (*this);
}

uint *BigInt::getNumbers() const {
    return numbers;
}

size_t BigInt::getSize() const {
    return sizeOfNumbers;
}


bool BigInt::getIsNegative() const {
    return isNegative;
}

BigInt BigInt::addWithoutSign(const BigInt &bigNum) const {
    BigInt result;
    result.isNegative = isNegative;
    result.sizeOfNumbers = (*this).sizeOfNumbers;
    size_t minimumTerm = bigNum.sizeOfNumbers;
    bool isThisBigger = true;
    if (bigNum.sizeOfNumbers > result.sizeOfNumbers) {
        result.sizeOfNumbers = bigNum.sizeOfNumbers;
        minimumTerm = (*this).sizeOfNumbers;
        isThisBigger = false;
    }
    result.numbers = new uint[sizeOfNumbers + 1];
    uint carry = 0;
    for (size_t i = 0; i < minimumTerm; i++) {
        result.numbers[i] = numbers[i] + bigNum.numbers[i] + carry;
        carry = result.numbers[i] / BASE;
        result.numbers[i] %= BASE;
    }

    const BigInt *ptrToBiggerNum = isThisBigger ? this : &bigNum;

    for (size_t i = minimumTerm; i < result.sizeOfNumbers; i++) {
        result.numbers[i] = ptrToBiggerNum->numbers[i] + carry;
        carry = result.numbers[i] / BASE;
        result.numbers[i] %= BASE;
    }
    if (carry != 0) {
        result.numbers[result.sizeOfNumbers++] = carry;
    }
    return result;
}

BigInt operator+(const BigInt &leftBig, const BigInt &rightBig) {
    if (!(leftBig.isNegative ^ rightBig.isNegative)) {
        BigInt result = leftBig.addWithoutSign(rightBig);
        result.isNegative = leftBig.getIsNegative();
        return result;
    }
    if (leftBig > rightBig) {
        if (leftBig > (-rightBig)) {
            return leftBig.subWithoutSign(rightBig);
        } else {
            return -rightBig.subWithoutSign(leftBig);
        }
    }
    if (rightBig > (-leftBig)) {
        return rightBig.subWithoutSign(leftBig);
    }
    return -leftBig.subWithoutSign(rightBig);
}

BigInt BigInt::subWithoutSign(const BigInt &bigNum) const {
    BigInt result;
    result.isNegative = false;
    result.sizeOfNumbers = sizeOfNumbers;
    result.numbers = new uint[sizeOfNumbers];

    bool needABorrow = false;

    for (size_t i = 0; i < bigNum.sizeOfNumbers; i++) {
        if (numbers[i] < bigNum.numbers[i] || (needABorrow && numbers[i] == bigNum.numbers[i])) {
            result.numbers[i] = BASE - (needABorrow ? 1 : 0);
            needABorrow = true;
            result.numbers[i] += (numbers[i] - bigNum.numbers[i]);
        } else {
            result.numbers[i] = (numbers[i] - bigNum.numbers[i]) - (needABorrow ? 1 : 0);
            needABorrow = false;
        }
        result.numbers[i] %= BASE;
    }

    for (size_t i = bigNum.sizeOfNumbers; i < sizeOfNumbers; i++) {
        if (numbers[i] == 0 && needABorrow) {
            result.numbers[i] = BASE - 1;
            needABorrow = true;
        } else {
            result.numbers[i] = numbers[i] - (needABorrow ? 1 : 0);
            needABorrow = false;
        }
    }

    for (int i = sizeOfNumbers - 1; i > 0 && result.numbers[i] == 0; i--) {
        result.sizeOfNumbers--;
    }

    return result;
}

BigInt BigInt::operator-() const {
    BigInt copyOfThis = BigInt(*this);
    if (this->sizeOfNumbers < 1 || this->numbers[0] == 0) {
        return copyOfThis;
    }
    copyOfThis.isNegative = !this->isNegative;
    return copyOfThis;
}

BigInt operator-(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig + (-rightBig);
}

int BigInt::comparator(const BigInt &bigNum) const {

    if (this->isNegative ^ bigNum.isNegative) {
        if (this->isNegative && !bigNum.isNegative) {
            return -1;
        } else {
            return 1;
        }
    }

    bool bothNegative = this->isNegative;

    if (this->sizeOfNumbers > bigNum.sizeOfNumbers) {
        return bothNegative ? -1 : 1;
    } else if (this->sizeOfNumbers < bigNum.sizeOfNumbers) {
        return bothNegative ? 1 : -1;
    }

    for (int i = sizeOfNumbers - 1; i >= 0; i--) {
        if (numbers[i] != bigNum.numbers[i]) {
            if (numbers[i] > bigNum.numbers[i]) {
                return bothNegative ? -1 : 1;
            } else {
                return bothNegative ? 1 : -1;
            }
        }
    }
    return 0;
}

bool operator<(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig.comparator(rightBig) == -1;
}

bool operator>(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig.comparator(rightBig) == 1;
}

bool operator<=(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig.comparator(rightBig) < 1;
}

bool operator>=(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig.comparator(rightBig) > -1;
}

bool operator==(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig.comparator(rightBig) == 0;
}

bool operator!=(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig.comparator(rightBig) != 0;
}

std::ostream &operator<<(std::ostream &out, const BigInt &bigNum) {
    if (bigNum.isNegative) {
        out << "-";
    }
    size_t size = bigNum.sizeOfNumbers;
    out << bigNum.numbers[size - 1];
    for (size_t i = 1; i < size; i++) {
        out << std::setw(BigInt::NUMDIG) << std::setfill('0') << bigNum.numbers[size - 1 - i];
    }

    return out;
}

BigInt operator*(const BigInt &leftBig, const BigInt &rightBig) {
    return leftBig.multiplication(rightBig);
}

BigInt BigInt::multiplication(const BigInt &bigNum) const {
    BigInt result;
    result.isNegative = this->isNegative ^ bigNum.isNegative;
    result.sizeOfNumbers = this->sizeOfNumbers + bigNum.sizeOfNumbers;
    result.numbers = new uint[result.sizeOfNumbers];
    for (size_t i = 0; i < result.sizeOfNumbers; i++) {
        result.numbers[i] = 0;
    }
    uint multiplicationMatrix[bigNum.sizeOfNumbers][this->sizeOfNumbers + 1];
    int rowSize = bigNum.sizeOfNumbers;
    int columnSize = this->sizeOfNumbers + 1;
    uint carry = 0;
    for (int i = 0; i < rowSize; i++) {
        carry = 0;
        for (int j = 0; j < columnSize - 1; j++) {
            multiplicationMatrix[i][j] = (this->numbers[j] * bigNum.numbers[i] + carry);
            carry = multiplicationMatrix[i][j] / BASE;
            multiplicationMatrix[i][j] %= BASE;
        }
        multiplicationMatrix[i][this->sizeOfNumbers] = carry;
    }

    carry = 0;
    for (int i = 0; i < result.sizeOfNumbers; i++) {
        int rowIndex = 0;
        int columnIndex = i;
        while (columnIndex > columnSize - 1) {
            columnIndex--;
            rowIndex++;
        }
        while (rowIndex < rowSize && columnIndex >= 0) {
            result.numbers[i] += (multiplicationMatrix[rowIndex][columnIndex]);
            rowIndex++;
            columnIndex--;
        }
        result.numbers[i] += carry;
        carry = result.numbers[i] / BASE;
        result.numbers[i] %= BASE;
    }


    for (int i = result.sizeOfNumbers - 1; i > 0 && result.numbers[i] == 0; i--) {
        result.sizeOfNumbers--;
    }

    return result;
}
