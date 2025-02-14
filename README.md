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

## TL;DR
### Project Setup
* Used Git submodules for external dependencies.
* Established CMake build system.

### Design Choices
* Introduced Role, Employee, and Company classes. Later optimized by attaching an employee count directly to Role to avoid object overhead.

### Performance Optimization
* Reduced creation time from ~10000ms to 80ms and salary updates from ~95ms to 13ms.
    * Switched from unordered maps to vectors for better memory locality.
    * Removed unnecessary object creation and used preallocation where possible.
* Tried parallel data reading but encountered mutex contention and worsen the performance.

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

## 2024-02-10
- [x] Create a script to generate random data
- [x] Create a RAII class to measure time

### Notes
* Today I want to focus on creating the tools to allow me do performance test. First I'd like to test in scenarios were we have a lot of data. For that I'll create a small script to generate it. After that I'll create a simple profiler so I can instrument the code. Finally, I'll also will do some VTune passes, but I want to have the timers in case I want to profile a specific part of the code.

## 2024-02-12
- [x] Instument and stress test
- [x] Optimize
- [ ] Make a VTune pass

### Notes
* I created a profiling branch to show and explain each change, I wont upload all intermediatte steps to the main branch. Only the optimizations that we need.
* Instrumenting main in parse data and in salary increase it shows that there is room for improvement in both, but most of the time is reading the data. It makes sense because there Im creating all the objects, I'll take a closer look at the function.
* Before keep diging into performance, I would like to improve a bit the way Im parsing the file. I want to have a generic file parser that return a vector for each line with the proper type. Also, I'd like to localize things specific to the company or bussiness logic in general outside of the parser. After decopuling the parser, I'll profile the bussiness logic instead of the reading part.
* After the refactor, only profiling the construction of the company and the increase of salaries we get 9979.03 ms for the construction and 112.769 ms for incrementing all salaries.
    * I tried to remove the employee creation that we were maintaining for future flexibility and the construction went  to 1142.55 ms. Preallocating the whole vector gives a good middle point of 2299.17 ms. But if we really want to go downt to 1142.55 ms we could make employee count just an attribute of the role.
    * I tried to bump the version to C++20 so I can use [[likely]] and [[unlikely]] for the branch I have in creation where the "None" case is not so common for the data but it turned out to be worse (3267.4 ms).
    * The only other way I can think at the moment I can optimize the creation is with preallocated roles. Or as we said before by making the employees just a role number. 
* For the time being I'll focus on salary increse, as I think there are some low-hanging fruits. 

## 2024-02-12
- [x] Make VTune pass

### Notes
* I overlooked a big one. I forgot to activate optimizations when compiling in performance mode. That gave a big boost on perf, leaving it at 692.771 ms for creation and 95.6345 ms for increasing the salaries.
* I tried reading the rows vector in chunks with a shared mutex and process it in parallel but it was actually worse. Im assuming thats because of contention.
* What seems to have improve the performance is preallocating the hashmap, leaving us in 496.482 ms at creation time (about 200ms improvement)
* After some analysis in VTune, we were having a bottleneck in the constructor when adding the roles. It turns out that our memory access was not optimal, and we were also having several cache misses. Instead of using an unordered map I'll use a vector per role type. The rationale is the following:
    * We only access roles in the tests, so its ok if we make access slower in favor of quicker writes. Now for finding a key, we will need to iterate over the vectors.
    * The "seniority" vector will be first class citizen, we'll assume that most of the time we'll use that which seems to be what the data reflects.
    * Also, since we're paying more atention to the actual data for this optimization part, I'll get rid of the void employees struct and mantain just a number.
* That had pretty good results
    * Creation time today went from 692.771ms to 80ms and increasing salary time went from 95.6345ms to 13ms. 
    * This side effect of also working well for the increase operation is likely due to cache locality.
* At this point the only new thing that VTune suggest is to improve parallelism, which I agree but it gives high contention leaving too poorer results in the last try.