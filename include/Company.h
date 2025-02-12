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
    std::unordered_map<RoleKey, RolePtr> m_roles;
public:
    // Increase salaries for all roles
    void incrementSalaries();

    template<typename T>
    void addRole(const std::shared_ptr<T>& role)
    {
        RoleKey key;
        if constexpr (std::is_same_v<T, SeniorityRole>)
        {
            key = {role->getDepartment(), role->getSeniority()};
        }
        else
        {
            key = {role->getDepartment(), std::nullopt};
        }
        m_roles[key] = role;
    }
    
    std::optional<RolePtr> getRole(const RoleKey& key) const;
};

using CompanyPtr = std::shared_ptr<Company>;

} // namespace ppp


