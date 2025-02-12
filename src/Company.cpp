#include "Company.h"

#include "utils/Parser.h"

void ppp::Company::incrementSalaries()
{
    for(const auto& rolesIt : m_roles)
    {
        rolesIt.second->increaseSalary();
    }
}

std::optional<ppp::RolePtr> ppp::Company::getRole(const RoleKey &key) const
{
    auto roleIt = m_roles.find(key);
    if(roleIt == m_roles.end())
    {
        return std::nullopt;
    }
    return roleIt->second;
}
