#pragma once

#include "Role.h"

#include <unordered_map>
#include <string>
#include <optional>
#include <memory>
#include <type_traits>

namespace ppp
{

class Company
{
private:
    std::vector<SeniorityRole> m_seniority_roles;
    std::vector<Role> m_roles;

public:
    Company(const std::string& file_path);

    // Increase salaries for all roles
    void incrementSalaries();

    template<typename T>
    void addRole(const T& role)
    {
        if constexpr (std::is_same_v<SeniorityRole, T>)
        {
            m_seniority_roles.push_back(role);
        }
        else if constexpr (std::is_same_v<Role, T>)
        {
            m_roles.push_back(role);
        }
    }
    
    std::optional<RolePtr> getRole(const RoleKey& key) const;
};

using CompanyPtr = std::shared_ptr<Company>;

} // namespace ppp


