#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace ppp
{

struct RoleKey
{
    std::string department;
    std::optional<std::string> seniority;

    RoleKey() = default;
   
    RoleKey(const std::string& department, std::optional<std::string> seniority = std::nullopt)
        : department(department), seniority(seniority) {}
    
    bool operator==(const RoleKey& other) const
    {
        return department == other.department
            && seniority == other.seniority;
    }
};


class Role
{
protected:
    std::string m_department;
    float m_salary;
    float m_increment_percentage;
    int m_employees_number;
public:
    Role(std::string department, float salary, float increment_percentage, int employees_number) :
        m_department{std::move(department)}, m_salary{salary}, m_increment_percentage{increment_percentage},
        m_employees_number{employees_number} 
    {};

    virtual ~Role() = default;

    inline float getSalary() const
    {
        return m_salary;
    }

    inline float getSalaryIncrementPercentage() const
    {
        return m_increment_percentage;
    }

    inline std::string getDepartment() const 
    {
        return m_department;
    }
    
    virtual bool matchesKey(const RoleKey& key) const;

    inline int getEmployeeCount() const
    {
        return m_employees_number;
    }
    
    void increaseSalary();
};

class SeniorityRole : public Role
{
private:
    std::string m_seniority;

public:
    SeniorityRole(std::string department, float salary, float increment_percentage, int employees_number, std::string seniority) :
        Role(department, salary, increment_percentage, employees_number), m_seniority{std::move(seniority)}
    {};


    inline std::string getSeniority() const
    {
        return m_seniority;
    }

    bool matchesKey(const RoleKey& key) const override;
};

using RolePtr = std::shared_ptr<Role>;

} // namespace ppp

namespace std
{
    template<>
    struct hash<ppp::RoleKey>
    {
        std::size_t operator()(const ppp::RoleKey& key) const
        {
            std::size_t h1 = std::hash<std::string>()(key.department);
            std::size_t h2 = key.seniority ? std::hash<std::string>()(key.seniority.value()) : 0;
            return h1 ^ (h2 << 1);
        }
    };
} // namespace std
