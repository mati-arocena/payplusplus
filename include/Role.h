#pragma once

#include "Employee.h"

#include <string>
#include <vector>

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
    float getSalary() const;
    float getSalaryIncrementPercentage() const;
    
    void increaseSalary();

    int getEmployeeCount() const;

    void addEmployee(const Employee& e);
};

} // namespace ppp
