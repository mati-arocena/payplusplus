#include "utils/Parser.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::optional<ppp::CompanyPtr> ppp::utils::Parser::parseCSV(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file: " << filename << "\n";
        return std::nullopt;
    }

    std::string header;
    if (!std::getline(file, header))
    {
        std::cerr << "Failed to read the header line from the file: " << filename << "\n";
        return std::nullopt;
    }


    ppp::Company company;
    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream lineStream(line);
        std::string department;
        std::string seniority;
        std::string salaryStr;
        std::string incrementStr;
        std::string employeeCountStr;
        float salary;
        float increment;
        int employeeCount;

        std::getline(lineStream, department, ',');
        std::getline(lineStream, seniority, ',');
        std::getline(lineStream, salaryStr, ',');
        std::getline(lineStream, incrementStr, ',');
        std::getline(lineStream, employeeCountStr, ',');

        try
        {
            salary = std::stof(salaryStr);
            increment = std::stof(incrementStr);
            employeeCount = std::stoi(employeeCountStr);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Invalid number format in CSV file: " << e.what() << "\n";
            return std::nullopt;
        }


        RolePtr role;
        if (seniority == "None")
        {
            role = std::make_shared<ppp::Role>(department, salary, increment);
            company.addRole(role);
        }
        else
        {
            std::shared_ptr<SeniorityRole> thisRole = std::make_shared<ppp::SeniorityRole>(department, salary, increment, seniority);
            role = thisRole;
            company.addRole(thisRole);
        }

        for (int i = 0; i < employeeCount; ++i)
        {
            ppp::Employee employee;
            role->addEmployee(employee);
        }
    }

    file.close();
    return std::make_shared<ppp::Company>(company);
}