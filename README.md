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
- [ ] Create test setup and tear down with test data

### Notes
