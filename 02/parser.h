//
// Created by kirill on 16.10.2020.
//

#ifndef MSU_CPP_AUTUMN_2020_PARSER_H
#define MSU_CPP_AUTUMN_2020_PARSER_H

using beforeParser = std::function<std::string()>;
using afterParser = std::function<int()>;
using doIfNumber = std::function<int(int)>;
using doIfString = std::function<std::string(std::string &)>;


void setBeforeParser(beforeParser callback);

void setAfterParser(afterParser callback);

void setDoIfNumber(doIfNumber callback);

void setDoIfString(doIfString callback);

void resetBeforeParser();

void resetAfterParser();

void resetDoIfNumber();

void resetDoIfString();

bool isNumber(std::string token);

void parser(const std::string &text, std::vector<std::string> &string_res,
            std::vector<int> &int_res);

#endif //MSU_CPP_AUTUMN_2020_PARSER_H
