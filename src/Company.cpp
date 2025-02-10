#include "Company.h"

std::optional<ppp::RolePtr> ppp::Company::getRole(const RoleKey &key) const
{
    auto roleIt = m_roles.find(key);
    if(roleIt == m_roles.end())
    {
        return std::nullopt;
    }
    return roleIt->second;
}
