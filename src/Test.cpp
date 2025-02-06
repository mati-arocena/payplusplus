#include "Test.h"

#include <iostream>

namespace ppp
{

void Test::IsCMakeWorking()
{
    std::cout << "CMake Is Working! :)" << "\n";
}

int Test::add(int num1, int num2) {
    return num1 + num2;
}

} // namespace ppp
