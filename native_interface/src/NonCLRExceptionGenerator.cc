
#include <NonCLRExceptionGenerator.hh>

void NonCLRExceptionGenerator::GenerateException(const std::string& aMessage) {
    // This function generates a non-CLR exception with the given message.
    throw std::runtime_error(aMessage);
}
