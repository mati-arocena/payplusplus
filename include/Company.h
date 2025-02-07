#pragma once

#include "Role.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace ppp
{

class Company
{
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::shared_ptr<Role>>> m_roles;
public:
    void addRole(std::shared_ptr<Role> role);
    
    std::shared_ptr<Role> getRole(std::string department, std::string seniority);
};

} // namespace ppp
