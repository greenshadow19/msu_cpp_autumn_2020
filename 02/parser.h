//
// Created by kirill on 16.10.2020.
//

#ifndef MSU_CPP_AUTUMN_2020_PARSER_H
#define MSU_CPP_AUTUMN_2020_PARSER_H

using beforeParser = std::string (*)();
using afterParser = int (*)();
using doIfNumber = int (*)(int);
using doIfString = std::string (*)(std::string &);

void setBeforeParser(beforeParser callback);

void setAfterParser(afterParser callback);

void setDoIfNumber(doIfNumber callback);

void setDoIfString(doIfString callback);

void resetBeforeParser();

void resetAfterParser();

void resetDoIfNumber();

void resetDoIfString();

bool isNumber(std::string token);

void parser(const char *text, std::vector<std::string> &string_res,
            std::vector<int> &int_res);

#endif //MSU_CPP_AUTUMN_2020_PARSER_H
