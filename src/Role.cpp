#include "Role.h"

float ppp::Role::getSalary() const
{
    return m_salary;
}

float ppp::Role::getSalaryIncrementPercentage() const
{
    return m_increment_percentage;
}

void ppp::Role::increaseSalary()
{
    m_salary += m_salary * m_increment_percentage;
}

int ppp::Role::getEmployeeCount() const
{
    return static_cast<int>(m_employees.size());
}

void ppp::Role::addEmployee(const Employee& employee)
{
    m_employees.push_back(employee);
}

std::string ppp::Role::getDepartment()
{
    return m_department;
}

std::string ppp::Role::getSeniority()
{
    return m_seniority;
}
