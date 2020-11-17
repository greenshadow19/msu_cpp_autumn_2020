//
// Created by kirill on 17.11.2020.
//

#ifndef MSU_CPP_AUTUMN_2020_FORMAT_H
#define MSU_CPP_AUTUMN_2020_FORMAT_H

#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <vector>

class Format {
private:
    size_t argSize;
    std::vector<std::string> formatArgsVector;

    template<class T, class... ArgsT>
    void getFormatArgs(T &&firstArg, ArgsT &&... argsT) {
        std::stringstream inStream;
        std::string stringArg;
        inStream << firstArg;
        inStream >> stringArg;
        formatArgsVector.push_back(stringArg);
        argSize++;
        getFormatArgs(std::forward<ArgsT>(argsT)...);
    }

    template<class T>
    void getFormatArgs(T &&lastArg) {
        std::stringstream inStream;
        std::string stringArg;
        inStream << lastArg;
        inStream >> stringArg;
        formatArgsVector.push_back(stringArg);
        argSize++;
    }

public:
    template<class... ArgsT>
    explicit Format(ArgsT &&... argsT) : argSize(0) {
        getFormatArgs(std::forward<ArgsT>(argsT)...);
    }

    size_t getArgSize() const {
        return argSize;
    }

    const std::string &operator[](size_t i) const {
        return formatArgsVector[i];
    }

};


template<class... ArgsT>
std::string format(const std::string &stringToFormat, ArgsT &&... argsT) {
    Format formatArgs(std::forward<ArgsT>(argsT)...);
    std::stringstream resultStringStream;

    size_t positionFormat = 0;
    size_t sizeOfString = stringToFormat.size();
    size_t sizeOfArgs = formatArgs.getArgSize();

    for (size_t i = 0; i < sizeOfString; i++) {
        if (stringToFormat[i] == '{') {
            if (stringToFormat[++i] == '}') {
                throw std::runtime_error("Empty format number");
            }
            positionFormat = 0;
            while (stringToFormat[i] != '}') {
                if (!isdigit(stringToFormat[i])) {
                    throw std::runtime_error("Not a number in the scope");
                }
                positionFormat *= 10;
                positionFormat += stringToFormat[i] - '0';
                i++;
            }
            if (positionFormat >= sizeOfArgs) {
                throw std::runtime_error("Format number exceeds limits");
            }
            resultStringStream << formatArgs[positionFormat];
        } else if (stringToFormat[i] == '}') {
            throw std::runtime_error("Closing before opening");
        } else {
            resultStringStream << stringToFormat[i];
        }
    }

    return resultStringStream.str();
}


#endif //MSU_CPP_AUTUMN_2020_FORMAT_H
