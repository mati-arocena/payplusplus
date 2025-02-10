# PayPlusPlus

# Build and Run
## Unix-like
```sh
mkdir build
cd build
cmake ..
cmake --build .

ctest
```

# Devlog
## 2024-02-05
- [x] Create project structure and CMakeLists
- [x] Include a testing library
- [x] Ignore ctidy in external folder
- [ ] Create dummy interfaces
- [ ] Create unit tests

### Notes
* I'll use git submodules for external libraries. Although I don't expect a lot of them. Probably just the tests.

## 2024-02-07
- [x] Create unit tests
- [x] Create dummy interfaces

### Notes
* I'll start by creating the unit test specifyied in the exercise. Those test will assume a dummy interface to check against. To start, I'll choose a naive approach for the interface so I can make the test compile, it will probably change in the future.
* For now Im thinking of the following structure:
    * A class Role, that holds information about department (HR, Engenieering, etc), seniority and salary.
    * A class Employee, that has a role associated.
    * A class Company, that acts as container or manager for the two.
* Im realizing that having an Employee class with the Role associated will be slow for what we're interested. For example, if we want to count the employees associated with a specific role, we'll have to iterate over the employees and then check the role for each one. 
    * There are multiple ways to solve the issue, we could just add a counter of employees to each role, but for the sake of the exersice and to provide extensibility lets add an array of employees to the role. That way if we're interested in data from the employee would be easier to adapt.
* I more or less get to a base API but Im not a fan. I'll commit the WIP, but Im missing improving the interface for roles that doesn't have a seniority, and fix ctidy warnings.

## 2024-02-08
- [x] Fix compilation warnings
- [x] Do a naive implementation of the methods so the tests passes
- [x] Create test setup and tear down with test data

### Notes
* The test are compiling with some hardcoded data. For the next steps I would like to read the data from files to add some flexibility. After that I can start to think in better design and performance.

## 2024-02-09
- [x] Read data from a text file
- [x] Improve API design

### Notes
* Before focusing on performance I think I'll start by reading the data from a text file so Im able to test with different or big input.
* Now, I'll try to improve the API for the CEO role, which is a role that doesn't actually have a seniority. Also, in the future we could add more roles with specific properties like contractors.
    * The solution should also be flexible enough so we can still read from files and add roles dynamically, so I discard things like enums. I still want to treat the roles uniformaly since the behaivor doesn't change, there is only a small variation in the data.
    * One simple fix could be to just have some sort of composition, where role and seniority as different classes, and seniority could be a pointer. But I don't think this quite matches the problem, the salary increases are associated with specific seniorities in a department, so it would make sense that the seniority has the increasePersentage and salary data. However we would need to treat the CEO in a special way since he also has salary and increase but doesnt have any seniority.
    * I think I would rather do a subtype for it, and then change Company to accept multiple types.
    * For handling the different types of Roles in Company, I recon it would be simpler to just use function overloading with `addRole(const Role& role)` and `addRole(const SeniorityRole& role)` but I want some excuse to use templates and constexpr.
    * Today Im kind of happy of how the API turned out. Next I'll continue with performance optimization. I'll create a script to generate a bunch of entries to stress test the app.