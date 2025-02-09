#include <gtest/gtest.h>

#include "Company.h"
#include "Role.h"

#include "utils/Parser.h"

class SalaryTest : public ::testing::Test {
protected:
    ppp::Company company;

    void SetUp() override {
        auto maybeCompany = ppp::utils::Parser::parseCSV("../data/tests.csv");
        if(!maybeCompany.has_value())
        {
            FAIL() << "Failed to parse CSV.";
        }

        company = *maybeCompany.value();
    }
};

TEST_F(SalaryTest, EmployeeCount) {
    {
        auto maybeRole = company.getRole("HR", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 5);
    }
    {
        auto maybeRole = company.getRole("HR", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 2);
    }
    {
        auto maybeRole = company.getRole("HR", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 13);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 50);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 68);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 32);
    }
    {
        auto maybeRole = company.getRole("Artist", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 5);
    }
    {
        auto maybeRole = company.getRole("Artist", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 20);
    }
    {
        auto maybeRole = company.getRole("Design", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 10);
    }
    {
        auto maybeRole = company.getRole("Design", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 15);
    }
    {
        auto maybeRole = company.getRole("PM", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 10);
    }
    {
        auto maybeRole = company.getRole("PM", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 15);
    }
    {
        auto maybeRole = company.getRole("CEO", "CEO");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_EQ(maybeRole.value()->getEmployeeCount(), 1);
    }
}

TEST_F(SalaryTest, IncrementPercentage) {
    {
        auto maybeRole = company.getRole("HR", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.5f);
    }
    {
        auto maybeRole = company.getRole("HR", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.2f);
    }
    {
        auto maybeRole = company.getRole("HR", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.05f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.1f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.07f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.05f);
    }
    {
        auto maybeRole = company.getRole("Artist", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.05f);
    }
    {
        auto maybeRole = company.getRole("Artist", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.025f);
    }
    {
        auto maybeRole = company.getRole("Design", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.07f);
    }
    {
        auto maybeRole = company.getRole("Design", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.04f);
    }
    {
        auto maybeRole = company.getRole("PM", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.1f);
    }
    {
        auto maybeRole = company.getRole("PM", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 0.05f);
    }
    {
        auto maybeRole = company.getRole("CEO", "CEO");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalaryIncrementPercentage(), 1.0f);
    }
}

TEST_F(SalaryTest, BaseSalary) {
    {
        auto maybeRole = company.getRole("HR", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1500.0f);
    }
    {
        auto maybeRole = company.getRole("HR", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1000.0f);
    }
    {
        auto maybeRole = company.getRole("HR", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 500.0f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 5000.0f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 3000.0f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1500.0f);
    }
    {
        auto maybeRole = company.getRole("Artist", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2000.0f);
    }
    {
        auto maybeRole = company.getRole("Artist", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1200.0f);
    }
    {
        auto maybeRole = company.getRole("Design", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2000.0f);
    }
    {
        auto maybeRole = company.getRole("Design", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 800.0f);
    }
    {
        auto maybeRole = company.getRole("PM", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 4000.0f);
    }
    {
        auto maybeRole = company.getRole("PM", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2400.0f);
    }
    {
        auto maybeRole = company.getRole("CEO", "CEO");
        ASSERT_TRUE(maybeRole.has_value());
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2000.0f);
    }
}

TEST_F(SalaryTest, IncreaseSalary) {
    {
        auto maybeRole = company.getRole("HR", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1500 * 1.5f);
    }
    {
        auto maybeRole = company.getRole("HR", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1000 * 1.2f);
    }
    {
        auto maybeRole = company.getRole("HR", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 500 * 1.05f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 5000 * 1.1f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 3000 * 1.07f);
    }
    {
        auto maybeRole = company.getRole("Engineering", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1500 * 1.05f);
    }
    {
        auto maybeRole = company.getRole("Artist", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2000 * 1.05f);
    }
    {
        auto maybeRole = company.getRole("Artist", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 1200 * 1.025f);
    }
    {
        auto maybeRole = company.getRole("Design", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2000 * 1.07f);
    }
    {
        auto maybeRole = company.getRole("Design", "Junior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 800 * 1.04f);
    }
    {
        auto maybeRole = company.getRole("PM", "Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 4000 * 1.1f);
    }
    {
        auto maybeRole = company.getRole("PM", "Semi Senior");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2400 * 1.05f);
    }
    {
        auto maybeRole = company.getRole("CEO", "CEO");
        ASSERT_TRUE(maybeRole.has_value());
        maybeRole.value()->increaseSalary();
        EXPECT_FLOAT_EQ(maybeRole.value()->getSalary(), 2000 * 2.0f);
    }
}


