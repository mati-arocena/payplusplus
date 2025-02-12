#include "Company.h"
#include "utils/Parser.h"
#include "utils/Profiler.h"

int main()
{
    std::optional<ppp::Company> maybeCompany;
    {
        SCOPED_PROF("Reading data");
        maybeCompany = ppp::utils::Parser::parseCSV("../data/stress_test.csv");
    }

    {
        SCOPED_PROF("Applying salary increase");
        if (maybeCompany.has_value())
        {
            maybeCompany->incrementSalaries();
        }
    }

}