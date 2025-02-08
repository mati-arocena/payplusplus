#pragma once

#include "Employee.h"

#include <string>
#include <vector>
#include <memory>

namespace ppp
{

class Role
{
private:
    std::string m_department;
    std::string m_seniority;
    float m_salary;
    float m_increment_percentage;
    std::vector<Employee> m_employees;
public:
    Role(std::string department, std::string seniority, float salary, float increment_percentage) :
        m_department{std::move(department)}, m_seniority{std::move(seniority)}, m_salary{salary}, m_increment_percentage{increment_percentage} 
    {};

    float getSalary() const;
    float getSalaryIncrementPercentage() const;
    
    void increaseSalary();

    int getEmployeeCount() const;

    void addEmployee(const Employee& employee);

    std::string getDepartment();
    std::string getSeniority();
};

using RolePtr = std::shared_ptr<Role>;

} // namespace ppp
