//
// Created by kirill on 08.11.2020.
//

#include "serializer.h"

void Serializer::handler(bool expression) {
    outStream << (expression ? "true" : "false") << Separator;
}

void Serializer::handler(uint64_t number) {
    outStream << number << Separator;
}

Error Deserializer::handler(bool &expression) {
    std::string stringExpression;
    inStream >> stringExpression;
    if (stringExpression == "true") {
        expression = true;
    } else if (stringExpression == "false") {
        expression = false;
    } else {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

Error Deserializer::handler(uint64_t &number) {
    std::string stringNumber;
    inStream >> stringNumber;
    try {
        if (stringNumber[0] == '-') {
            return Error::CorruptedArchive;
        }
        number = std::stoull(stringNumber);
    } catch (const std::exception &exception) {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}
