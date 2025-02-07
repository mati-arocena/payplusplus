#include <gtest/gtest.h>

#include "Company.h"
#include "Role.h"

class SalaryTest : public ::testing::Test {
protected:
    Company company;

    void SetUp() override {

    }

    void TearDown() override {

    }
};

TEST_F(SalaryTest, EmployeeCount) {
    EXPECT_EQ(company.getRole("HR", "Senior").getEmployeeCount(), 5);
    EXPECT_EQ(company.getRole("HR", "Semi Senior").getEmployeeCount(), 2);
    EXPECT_EQ(company.getRole("HR", "Junior").getEmployeeCount(), 13);
    
    EXPECT_EQ(company.getRole("Engineering", "Senior").getEmployeeCount(), 50);
    EXPECT_EQ(company.getRole("Engineering", "Semi Senior").getEmployeeCount(), 68);
    EXPECT_EQ(company.getRole("Engineering", "Junior").getEmployeeCount(), 32);

    EXPECT_EQ(company.getRole("Artist", "Senior").getEmployeeCount(), 5);
    EXPECT_EQ(company.getRole("Artist", "Semi Senior").getEmployeeCount(), 20);

    EXPECT_EQ(company.getRole("Design", "Senior").getEmployeeCount(), 10);
    EXPECT_EQ(company.getRole("Design", "Junior").getEmployeeCount(), 15);

    EXPECT_EQ(company.getRole("PM", "Senior").getEmployeeCount(), 10);
    EXPECT_EQ(company.getRole("PM", "Semi Senior").getEmployeeCount(), 15);          

    EXPECT_EQ(company.getRole("CEO", "CEO").getEmployeeCount(), 1); //Not too happy with this API  
}

TEST_F(SalaryTest, IncrementPercentage) {
    EXPECT_FLOAT_EQ(company.getRole("HR", "Senior").getSalaryIncrementPercentage(), 0.5f);
    EXPECT_FLOAT_EQ(company.getRole("HR", "Semi Senior").getSalaryIncrementPercentage(), 0.2f);
    EXPECT_FLOAT_EQ(company.getRole("HR", "Junior").getSalaryIncrementPercentage(), 0.05f);
    
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Senior").getSalaryIncrementPercentage(), 0.1f);
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Semi Senior").getSalaryIncrementPercentage(), 0.07f);
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Junior").getSalaryIncrementPercentage(), 0.05f);

    EXPECT_FLOAT_EQ(company.getRole("Artist", "Senior").getSalaryIncrementPercentage(), 0.05f);
    EXPECT_FLOAT_EQ(company.getRole("Artist", "Semi Senior").getSalaryIncrementPercentage(), 0.025f);

    EXPECT_FLOAT_EQ(company.getRole("Design", "Senior").getSalaryIncrementPercentage(), 0.07f);
    EXPECT_FLOAT_EQ(company.getRole("Design", "Junior").getSalaryIncrementPercentage(), 0.04f);

    EXPECT_FLOAT_EQ(company.getRole("PM", "Senior").getSalaryIncrementPercentage(), 0.1f);
    EXPECT_FLOAT_EQ(company.getRole("PM", "Semi Senior").getSalaryIncrementPercentage(), 0.05f);          

    EXPECT_FLOAT_EQ(company.getRole("CEO", "CEO").getSalaryIncrementPercentage(), 1.0f); 
}

TEST_F(SalaryTest, BaseSalary)
{
    EXPECT_FLOAT_EQ(company.getRole("HR", "Senior").getSalary(), 0.5f);
    EXPECT_FLOAT_EQ(company.getRole("HR", "Semi Senior").getSalary(), 0.2f);
    EXPECT_FLOAT_EQ(company.getRole("HR", "Junior").getSalary(), 0.05f);
    
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Senior").getSalary(), 0.1f);
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Semi Senior").getSalary(), 0.07f);
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Junior").getSalary(), 0.05f);

    EXPECT_FLOAT_EQ(company.getRole("Artist", "Senior").getSalary(), 0.05f);
    EXPECT_FLOAT_EQ(company.getRole("Artist", "Semi Senior").getSalary(), 0.025f);

    EXPECT_FLOAT_EQ(company.getRole("Design", "Senior").getSalary(), 0.07f);
    EXPECT_FLOAT_EQ(company.getRole("Design", "Junior").getSalary(), 0.04f);

    EXPECT_FLOAT_EQ(company.getRole("PM", "Senior").getSalary(), 0.1f);
    EXPECT_FLOAT_EQ(company.getRole("PM", "Semi Senior").getSalary(), 0.05f);          

    EXPECT_FLOAT_EQ(company.getRole("CEO", "CEO").getSalary(), 1.0f); 

}

TEST_F(SalaryTest, IncreaseSalary)
{
    company.getRole("HR", "Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("HR", "Senior").getSalary(), 1500 * 1.5f);

    company.getRole("HR", "Semi Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("HR", "Semi Senior").getSalary(), 1000 * 1.2f);
    
    company.getRole("HR", "Junior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("HR", "Junior").getSalary(), 500 * 1.05f);
    
    company.getRole("Engineering", "Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Senior").getSalary(), 5000 * 1.1f);

    company.getRole("Engineering", "Semi Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Semi Senior").getSalary(), 3000 * 1.07f);

    company.getRole("Engineering", "Junior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("Engineering", "Junior").getSalary(), 1500 * 1.05f);

    company.getRole("Artist", "Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("Artist", "Senior").getSalary(), 2000 * 1.05f);

    company.getRole("Artist", "Semi Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("Artist", "Semi Senior").getSalary(), 1200 * 1.025f);

    company.getRole("Design", "Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("Design", "Senior").getSalary(), 2000 * 1.07f);

    company.getRole("Design", "Junior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("Design", "Junior").getSalary(), 800 * 1.04f);

    company.getRole("PM", "Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("PM", "Senior").getSalary(), 4000 * 1.1f);
    
    company.getRole("PM", "Semi Senior").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("PM", "Semi Senior").getSalary(), 2400 * 1.05f);          

    company.getRole("CEO", "CEO").increaseSalary();
    EXPECT_FLOAT_EQ(company.getRole("CEO", "CEO").getSalary(), 2000 * 2.0f);
}
