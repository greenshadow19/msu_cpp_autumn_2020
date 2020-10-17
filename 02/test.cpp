//
// Created by kirill on 16.10.2020.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include "parser.h"

void SpaceTest() {
    const char *text = "\tfirst\n  second\t \tthird";
    std::vector<std::string> string_results;
    std::vector<int> int_results;
    setDoIfString([](std::string &token) -> std::string {
        return token;
    });
    parser(text, string_results, int_results);
    resetDoIfString();
    assert(string_results[0] == "first");
    assert(string_results[1] == "second");
    assert(string_results[2] == "third");
};

void IntTest() {
    const char *text = "2 sdfj 7 ;asjfkd 5";
    std::vector<std::string> string_results;
    std::vector<int> int_results;
    setDoIfNumber([](int num) -> int {
        return num * num;
    });
    parser(text, string_results, int_results);
    resetDoIfNumber();
    assert(int_results[0] == 4);
    assert(int_results[1] == 49);
    assert(int_results[2] == 25);
};

void StringTest() {
    const char *text = "2 CaMel TyPe TeXt 7 5";
    std::vector<std::string> string_results;
    std::vector<int> int_results;
    setDoIfString([](std::string &token) -> std::string {
        std::transform(token.begin(), token.end(), token.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return token;
    });
    parser(text, string_results, int_results);
    resetDoIfString();
    assert(string_results[0] == "camel");
    assert(string_results[1] == "type");
    assert(string_results[2] == "text");
}

void beforeTest() {
    const char *text = "some text";
    std::vector<std::string> string_results;
    std::vector<int> int_results;
    setBeforeParser([]() -> std::string {
        return "It happened before parser";
    });
    parser(text, string_results, int_results);
    resetBeforeParser();
    assert(string_results[0] == "It happened before parser");
}

void afterTest() {
    const char *text = "some text";
    std::vector<std::string> string_results;
    std::vector<int> int_results;
    setAfterParser([]() -> int {
        return 5;
    });
    parser(text, string_results, int_results);
    resetAfterParser();
    assert(int_results[0] == 5);
}

void resetTest() {
    const char *text = "CaMel";
    std::vector<std::string> string_results;
    std::vector<int> int_results;
    setDoIfString([](std::string &token) -> std::string {
        std::transform(token.begin(), token.end(), token.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return token;
    });
    parser(text, string_results, int_results);
    assert(string_results[0] == "camel");

    resetDoIfString();
    setDoIfString([](std::string &token) -> std::string {
        std::transform(token.begin(), token.end(), token.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return token;
    });
    parser(text, string_results, int_results);
    resetDoIfString();
    assert(string_results[1] == "CAMEL");
}

int main() {
    SpaceTest();
    IntTest();
    StringTest();
    beforeTest();
    afterTest();
    resetTest();
    std::cout << "Success" << std::endl;
    return 0;
}
