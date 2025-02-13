#pragma once

#include "Employee.h"

#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace ppp
{

class Role
{
private:
    std::string m_department;
    float m_salary;
    float m_increment_percentage;
    std::vector<Employee> m_employees;
public:
    Role(std::string department, float salary, float increment_percentage) :
        m_department{std::move(department)}, m_salary{salary}, m_increment_percentage{increment_percentage} 
    {};

    inline float getSalary() const
    {
        return m_salary;
    }

    inline float getSalaryIncrementPercentage() const
    {
        return m_increment_percentage;
    }

    inline std::string getDepartment() const 
    {
        return m_department;
    }
    
    int getEmployeeCount() const;
    
    void increaseSalary();

    void addEmployee(const Employee& employee);
};

class SeniorityRole : public Role
{
private:
    std::string m_seniority;

public:
    SeniorityRole(std::string department, float salary, float increment_percentage, std::string seniority) :
        Role(department, salary, increment_percentage), m_seniority{std::move(seniority)}
    {};


    inline std::string getSeniority() const
    {
        return m_seniority;
    }
};

using RolePtr = std::shared_ptr<Role>;

struct RoleKey
{
    std::string department;
    std::optional<std::string> seniority;

    RoleKey() = default;
   
    RoleKey(const std::string& department, std::optional<std::string> seniority = std::nullopt)
        : department(department), seniority(seniority) {}
    
    bool operator==(const RoleKey& other) const
    {
        return department == other.department
            && seniority == other.seniority;
    }
};

} // namespace ppp

namespace std
{
    template<>
    struct hash<ppp::RoleKey>
    {
        std::size_t operator()(const ppp::RoleKey& key) const
        {
            std::size_t h1 = std::hash<std::string>()(key.department);
            std::size_t h2 = key.seniority.has_value() ? std::hash<std::string>()(key.seniority.value()) : 0;
            return h1 ^ (h2 << 1);
        }
    };
} // namespace std
