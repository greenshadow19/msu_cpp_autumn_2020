//
// Created by kirill on 16.10.2020.
//
#include <string>
#include <vector>
#include "parser.h"

beforeParser before_parser = nullptr;
afterParser after_parser = nullptr;
doIfNumber do_if_number = nullptr;
doIfString do_if_string = nullptr;

void setBeforeParser(beforeParser callback) {
    before_parser = callback;
}

void setAfterParser(afterParser callback) {
    after_parser = callback;
}

void setDoIfNumber(doIfNumber callback) {
    do_if_number = callback;
}

void setDoIfString(doIfString callback) {
    do_if_string = callback;
}

void resetBeforeParser() {
    before_parser = nullptr;
}

void resetAfterParser() {
    after_parser = nullptr;
}

void resetDoIfNumber() {
    do_if_number = nullptr;
}

void resetDoIfString() {
    do_if_string = nullptr;
}

bool isNumber(std::string token) {
    size_t offset = 0;
    if (token[0] == '-') {
        offset = 1;
    }
    if (token[offset] == '0' && token.size() > offset) {
        return false;
    }
    for (int i = offset; i < token.size(); i++) {
        if (!std::isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

void parser(const char *text, std::vector<std::string> &string_res,
            std::vector<int> &int_res) {
    if (before_parser != nullptr) {
        string_res.push_back(before_parser());
    }
    std::string token;
    size_t size_of_token = 0;
    do {
        if (std::isspace(*text) || !(*text)) {
            if (size_of_token > 0) {
                if (isNumber(token)) {
                    if (do_if_number != nullptr) {
                        int_res.push_back(do_if_number(std::stoi(token)));
                    }
                } else {
                    if (do_if_string != nullptr) {
                        string_res.push_back(do_if_string(token));
                    }
                }
            }
            token = "";
            size_of_token = 0;
        } else {
            token.push_back(*text);
            size_of_token++;
        }
    } while (*(text++));

    if (after_parser != nullptr) {
        int_res.push_back(after_parser());
    }
}