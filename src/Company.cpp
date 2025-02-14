#include "Company.h"

#include "utils/Parser.h"
#include "utils/Profiler.h"

#include <algorithm>
#include <cmath>

namespace {
    constexpr double SENIORITY_RATIO = 0.9;
    constexpr double ROLE_RATIO = 0.1;
}

ppp::Company::Company(const std::string &file_path)
{
    auto rows = utils::Parser::parseCSV<std::string, std::string, float, float, int>(file_path);
    
    SCOPED_PROF("Company::Company");
    
    m_seniority_roles.reserve(std::ceil(static_cast<double>(rows.size()) * SENIORITY_RATIO));
    m_roles.reserve(std::ceil(static_cast<double>(rows.size()) * ROLE_RATIO));
    
    for (auto& row : rows)
    {
        std::string department = std::get<0>(row);
        std::string seniority = std::get<1>(row);
        float salary = std::get<2>(row);
        float increment_percentage = std::get<3>(row);
        int employee_count = std::get<4>(row);

        if (seniority == "None")
        {
            Role role(department, salary, increment_percentage, employee_count);
            addRole(role);
        }
        else
        {
            SeniorityRole role(department, salary, increment_percentage, employee_count, seniority);
            addRole(role);
        }
    }
}

void ppp::Company::incrementSalaries()
{
    SCOPED_PROF("Company::incrementSalaries");
    for(auto& role : m_seniority_roles)
    {
        role.increaseSalary();
    }
    for(auto& role : m_roles)
    {
        role.increaseSalary();
    }
}

std::optional<ppp::RolePtr> ppp::Company::getRole(const RoleKey &key) const
{
    auto seniority_roles_it = std::find_if(m_seniority_roles.begin(), m_seniority_roles.end(),
        [&key](const SeniorityRole& role) {
             return role.matchesKey(key); 
        });

    if (seniority_roles_it != m_seniority_roles.end())
    {
        return std::make_shared<ppp::SeniorityRole>(*seniority_roles_it);
    }

    auto roles_it = std::find_if(m_roles.begin(), m_roles.end(),
        [&key](const Role& role) {
             return role.matchesKey(key); 
        });

    if (roles_it != m_roles.end())
    {
        return std::make_shared<ppp::Role>(*roles_it);
    }

    return std::nullopt;    
}