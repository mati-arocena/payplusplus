#include "Role.h"

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
