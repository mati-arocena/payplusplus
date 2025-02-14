#include "Role.h"

void ppp::Role::increaseSalary()
{
    m_salary += m_salary * m_increment_percentage;
}

bool ppp::Role::matchesKey(const RoleKey& key) const
{
    return !key.seniority.has_value() && m_department == key.department;
}

bool ppp::SeniorityRole::matchesKey(const RoleKey& key) const
{
    return key.seniority.has_value() && m_seniority == *key.seniority && m_department == key.department;
}