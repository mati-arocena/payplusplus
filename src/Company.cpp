#include "Company.h"

#include "utils/Parser.h"
#include "utils/Profiler.h"

ppp::Company::Company(const std::string& file_path)
{
    auto rows = utils::Parser::parseCSV<std::string, std::string, float, float, int>(file_path);
    
    SCOPED_PROF("Company::Company");
    for (auto& row : rows)
    {
        std::string department = std::get<0>(row);
        std::string seniority = std::get<1>(row);
        float salary = std::get<2>(row);
        float increment_percentage = std::get<3>(row);
        int employee_count = std::get<4>(row);

        RolePtr role;
        if (seniority == "None")
        {
            role = std::make_shared<Role>(department, salary, increment_percentage);
            addRole(role);
        }
        else
        {
            role = std::make_shared<SeniorityRole>(department, salary, increment_percentage, seniority);
            addRole(std::static_pointer_cast<SeniorityRole>(role));
        }
        

        for (int i = 0; i < employee_count; i++)
        {
            role->addEmployee({});
        }
    }
}

void ppp::Company::incrementSalaries()
{
    SCOPED_PROF("Company::incrementSalaries");
    for(const auto& roles_it : m_roles)
    {
        roles_it.second->increaseSalary();
    }
}

std::optional<ppp::RolePtr> ppp::Company::getRole(const RoleKey &key) const
{
    auto roles_it = m_roles.find(key);
    if(roles_it == m_roles.end())
    {
        return std::nullopt;
    }
    return roles_it->second;
}
