cmake_minimum_required(VERSION 3.10)
project(PayPlusPlus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(ENABLE_DEBUG_BUILD "Enable Debug Build" OFF)
option(ENABLE_PERFORMANCE_TESTING "Enable Performance Testing" ON)

option(ENABLE_THREAD_SANITIZER "Enable Thread Sanitizer" OFF)
option(ENABLE_MEMORY_SANITIZER "Enable Memory Sanitizer" OFF)
option(ENABLE_TESTS "Enable Tests" OFF)

if (ENABLE_THREAD_SANITIZER)
    set(SANITIZER_FLAGS "-fsanitize=thread")
elseif (ENABLE_MEMORY_SANITIZER)
    set(SANITIZER_FLAGS "-fsanitize=memory" "-fsanitize-memory-track-origins" "-fno-omit-frame-pointer")
else()
    set(SANITIZER_FLAGS "")
endif()

if(ENABLE_DEBUG_BUILD)
    set(CMAKE_BUILD_TYPE "Debug")
    add_compile_options(-g -O0)
    add_compile_definitions(DEBUG_BUILD)
elseif (ENABLE_PERFORMANCE_TESTING)
    add_compile_options(-g -O0)
    add_compile_definitions(PERF_PROFILING)
else()
    set(PERFORMANCE_FLAGS "")
endif()

set(WARNING_FLAGS "-Wall" "-Wextra" "-Werror")

file(GLOB_RECURSE SRC_FILES "src/*.cpp")



add_executable(main ${SRC_FILES})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(main PRIVATE ${SANITIZER_FLAGS} ${PERFORMANCE_FLAGS} ${WARNING_FLAGS})
target_link_options(main PRIVATE ${SANITIZER_FLAGS})

set_target_properties(main PROPERTIES 
    CXX_CLANG_TIDY "clang-tidy;-p=${CMAKE_BINARY_DIR};-checks=clang-analyzer-*,bugprone-*,performance-*,portability-*,readability-*;--header-filter=^((?!external).*)$"
)

if (ENABLE_TESTS)
    set(GTEST_DIR ${CMAKE_SOURCE_DIR}/external/googletest)
    add_subdirectory(${GTEST_DIR})

    enable_testing()

    file(GLOB_RECURSE TEST_SRC_FILES "tests/*.cpp" "src/*.cpp")
    list(FILTER TEST_SRC_FILES EXCLUDE REGEX "src/main.cpp")

    add_executable(tests ${TEST_SRC_FILES})
    target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(tests PRIVATE gtest gtest_main pthread)
    target_compile_options(tests PRIVATE ${WARNING_FLAGS})

    add_test(NAME RunTests COMMAND tests)
endif()