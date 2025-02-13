#include "Company.h"
#include "utils/Parser.h"
#include "utils/Profiler.h"

#include <tuple>

int main()
{
    auto csv = ppp::utils::Parser::parseCSV<std::string, std::string, float, float, int>("../data/tests.csv");

    // std::optional<ppp::Company> maybeCompany;
    // {
    //     SCOPED_PROF("Reading data");
    //     maybeCompany = ppp::utils::Parser::parseCSV("../data/stress_test.csv");
    // }

    // {
    //     SCOPED_PROF("Applying salary increase");
    //     if (maybeCompany.has_value())
    //     {
    //         maybeCompany->incrementSalaries();
    //     }
    // }

}