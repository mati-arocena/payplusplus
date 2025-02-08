#include <gtest/gtest.h>

#include "Company.h"
#include "Role.h"

class SalaryTest : public ::testing::Test {
protected:
    ppp::Company company;

    void SetUp() override {
        auto hrSenior = std::make_shared<ppp::Role>("HR", "Senior", 1500, 0.5f);
        for (int i = 0; i < 5; ++i) {
            hrSenior->addEmployee(ppp::Employee());
        }
        company.addRole(hrSenior);

        auto hrSemiSenior = std::make_shared<ppp::Role>("HR", "Semi Senior", 1000, 0.2f);
        for (int i = 0; i < 2; ++i) {
            hrSemiSenior->addEmployee(ppp::Employee());
        }
        company.addRole(hrSemiSenior);

        auto hrJunior = std::make_shared<ppp::Role>("HR", "Junior", 500, 0.05f);
        for (int i = 0; i < 13; ++i) {
            hrJunior->addEmployee(ppp::Employee());
        }
        company.addRole(hrJunior);

        auto engSenior = std::make_shared<ppp::Role>("Engineering", "Senior", 5000, 0.1f);
        for (int i = 0; i < 50; ++i) {
            engSenior->addEmployee(ppp::Employee());
        }
        company.addRole(engSenior);

        auto engSemiSenior = std::make_shared<ppp::Role>("Engineering", "Semi Senior", 3000, 0.07f);
        for (int i = 0; i < 68; ++i) {
            engSemiSenior->addEmployee(ppp::Employee());
        }
        company.addRole(engSemiSenior);

        auto engJunior = std::make_shared<ppp::Role>("Engineering", "Junior", 1500, 0.05f);
        for (int i = 0; i < 32; ++i) {
            engJunior->addEmployee(ppp::Employee());
        }
        company.addRole(engJunior);

        auto artistSenior = std::make_shared<ppp::Role>("Artist", "Senior", 2000, 0.05f);
        for (int i = 0; i < 5; ++i) {
            artistSenior->addEmployee(ppp::Employee());
        }
        company.addRole(artistSenior);

        auto artistSemiSenior = std::make_shared<ppp::Role>("Artist", "Semi Senior", 1200, 0.025f);
        for (int i = 0; i < 20; ++i) {
            artistSemiSenior->addEmployee(ppp::Employee());
        }
        company.addRole(artistSemiSenior);

        auto designSenior = std::make_shared<ppp::Role>("Design", "Senior", 2000, 0.07f);
        for (int i = 0; i < 10; ++i) {
            designSenior->addEmployee(ppp::Employee());
        }
        company.addRole(designSenior);

        auto designJunior = std::make_shared<ppp::Role>("Design", "Junior", 800, 0.04f);
        for (int i = 0; i < 15; ++i) {
            designJunior->addEmployee(ppp::Employee());
        }
        company.addRole(designJunior);

        auto pmSenior = std::make_shared<ppp::Role>("PM", "Senior", 4000, 0.1f);
        for (int i = 0; i < 10; ++i) {
            pmSenior->addEmployee(ppp::Employee());
        }
        company.addRole(pmSenior);

        auto pmSemiSenior = std::make_shared<ppp::Role>("PM", "Semi Senior", 2400, 0.05f);
        for (int i = 0; i < 15; ++i) {
            pmSemiSenior->addEmployee(ppp::Employee());
        }
        company.addRole(pmSemiSenior);

        auto ceo = std::make_shared<ppp::Role>("CEO", "CEO", 2000, 1.0f);
        ceo->addEmployee(ppp::Employee());
        company.addRole(ceo);
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


