#pragma once

#include "Role.h"

#include <unordered_map>
#include <string>
#include <optional>
#include <memory>
#include <type_traits>
#include <shared_mutex>
#include <mutex>

namespace ppp
{

class Company
{
private:
    std::unordered_map<RoleKey, RolePtr> m_roles;

    mutable std::shared_mutex m_roles_mtx;
    
public:
    Company() = default;
    Company(const std::string& file_path);

    // Increase salaries for all roles
    void incrementSalaries();

    template<typename T>
    void addRole(const std::shared_ptr<T>& role)
    {
        std::unique_lock<std::shared_mutex> lock(m_roles_mtx);
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


