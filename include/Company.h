#pragma once

#include "Role.h"

#include <unordered_map>
#include <string>
#include <optional>
#include <memory>

namespace ppp
{

class Company
{
private:
    std::unordered_map<std::string, std::unordered_map<std::string, RolePtr>> m_roles;
public:
    void addRole(const RolePtr& role);
    
    std::optional<RolePtr> getRole(const std::string& department, const std::string& seniority) const;
};

using CompanyPtr = std::shared_ptr<Company>;

} // namespace ppp
