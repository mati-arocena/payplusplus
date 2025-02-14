#include "Company.h"

#include "utils/Parser.h"
#include "utils/Profiler.h"

#include <thread>

ppp::Company::Company(const std::string& file_path)
{
    auto rows = utils::Parser::parseCSV<std::string, std::string, float, float, int>(file_path);
    
    SCOPED_PROF("Company::Company");

    m_roles.reserve(rows.size());

    unsigned int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    auto chunkSize = (rows.size() + numThreads - 1) / numThreads;

    for (unsigned int i = 0; i < numThreads; ++i) {
        threads.emplace_back([this, &rows, i, chunkSize]() {
            auto start = rows.begin() + i * chunkSize;
            auto end = (i == std::thread::hardware_concurrency() - 1) ? rows.end() : start + chunkSize;
            for (auto it = start; it != end; ++it) {
                std::string department = std::get<0>(*it);
                std::string seniority = std::get<1>(*it);
                float salary = std::get<2>(*it);
                float increment_percentage = std::get<3>(*it);
                int employee_count = std::get<4>(*it);

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
                role->createEmployees(employee_count);
            }
        });
    }

    for (auto& t : threads) {
        t.join();
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
    std::shared_lock<std::shared_mutex> lock(m_roles_mtx);

    auto roles_it = m_roles.find(key);
    if(roles_it == m_roles.end())
    {
        return std::nullopt;
    }
    return roles_it->second;
}
