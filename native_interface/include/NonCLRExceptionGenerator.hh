
#pragma once

#include <stdexcept>
#include <string>

class NonCLRExceptionGenerator {
public:
    // This class is used to generate exceptions that are not CLR exceptions.
    NonCLRExceptionGenerator() = default;
    ~NonCLRExceptionGenerator() = default;

    // This function generates a non-CLR exception with the given message.
    static void GenerateException(const std::string& aMessage);
};
