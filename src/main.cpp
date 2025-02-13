#include "Company.h"
#include "utils/Parser.h"
#include "utils/Profiler.h"

#include <tuple>

int main()
{
    ppp::Company company("../data/stress_test.csv");
    company.incrementSalaries();
}