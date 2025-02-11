#include "utils/Parser.h"
#include "utils/Profiler.h"

int main()
{
    SCOPED_PROF("TEST");
    ppp::utils::Parser::parseCSV("../data/stress_test.csv");
}