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
- [>] Create dummy interfaces
- [>] Create unit tests
- [>] Ignore ctidy in external folder

### Notes
* I'll use git submodules for external libraries. Although I don't expect a lot of them. Probably just the tests.