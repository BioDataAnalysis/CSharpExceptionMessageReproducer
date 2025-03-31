
#pragma once

#pragma managed(push, off)
#include <cstdint>
#pragma managed(pop)

#include <vcclr.h>

public
ref class ExceptionMessageReproducer {
public:
    ExceptionMessageReproducer();
    ~ExceptionMessageReproducer();

    void test();

protected:
    !ExceptionMessageReproducer();
};
