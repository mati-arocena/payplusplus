#include "Company.h"

void ppp::Company::addRole(const RolePtr &role)
{
    auto roleIt = m_roles.find(role->getDepartment());
    if (roleIt == m_roles.end() ||
        roleIt->second.find(role->getSeniority()) == roleIt->second.end())
    {
        m_roles[role->getDepartment()][role->getSeniority()] = role;
    }
}

std::optional<ppp::RolePtr> ppp::Company::getRole(const std::string &department, const std::string &seniority) const //NOLINT(bugprone-easily-swappable-parameters) // TODO: Refactor this parameters
{
    auto roleIt = m_roles.find(department);
    if(roleIt == m_roles.end())
    {
        return std::nullopt;
    }

    auto secondRoleIt = roleIt->second.find(seniority);
    if(secondRoleIt == roleIt->second.end())
    {
        return std::nullopt;
    }

    return secondRoleIt->second;
}
