//
// Created by kirill on 17.11.2020.
//
#include <iostream>
#include <cassert>
#include "format.h"

void taskDescriptionTest() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}

void expectedWorkTest() {
    auto text = format("G_{1} {0} + Lambda/2 g_{1} {0} = 8*{2}*T_{1} {0}", "nu", "mu", "pi");
    auto inverseOrder = format("{2} {1} {0}", 3, 2, 1);
    auto floatNumbers = format("e = {0}", 2.71);

    assert(text == "G_mu nu + Lambda/2 g_mu nu = 8*pi*T_mu nu");
    assert(inverseOrder == "1 2 3");
    assert(floatNumbers == "e = 2.71");
}

void exceptionTest() {
    try {
        auto limitExceed = format("{5}", "one");
    } catch (const std::runtime_error &error) {
        std::string expectedError("Format number exceeds limits");
        assert(expectedError == error.what());
    }

    try {
        auto emptyFormat = format("{}", "one");
    } catch (const std::runtime_error &error) {
        std::string expectedError("Empty format number");
        assert(expectedError == error.what());
    }

    try {
        auto emptyFormat = format("{not}", "one");
    } catch (const std::runtime_error &error) {
        std::string expectedError("Not a number in the scope");
        assert(expectedError == error.what());
    }

    try {
        auto emptyFormat = format("}{", "one");
    } catch (const std::runtime_error &error) {
        std::string expectedError("Closing before opening");
        assert(expectedError == error.what());
    }

}

int main() {
    taskDescriptionTest();
    expectedWorkTest();
    exceptionTest();
    std::cout << "Success" << std::endl;
    return 0;
}
