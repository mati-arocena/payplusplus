cmake_minimum_required(VERSION 3.10)
project(PayPlusPlus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

option(ENABLE_THREAD_SANITIZER "Enable Thread Sanitizer" OFF)
option(ENABLE_MEMORY_SANITIZER "Enable Memory Sanitizer" OFF)
option(ENABLE_PERFORMANCE_TESTING "Enable Performance Testing" OFF)

if (ENABLE_THREAD_SANITIZER)
    set(SANITIZER_FLAGS "-fsanitize=thread")
elseif (ENABLE_MEMORY_SANITIZER)
    set(SANITIZER_FLAGS "-fsanitize=memory" "-fsanitize-memory-track-origins" "-fno-omit-frame-pointer")
else()
    set(SANITIZER_FLAGS "")
endif()

if (ENABLE_PERFORMANCE_TESTING)
    set(PERFORMANCE_FLAGS "-g" "-O2")
    # perf record -e cycles:u,instructions:u,cache-misses:u,context-switches -g ./main
else()
    set(PERFORMANCE_FLAGS "")
endif()

set(WARNING_FLAGS "-Wall" "-Wextra" "-Werror")

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=clang-analyzer-*,bugprone-*,performance-*,portability-*,readability-*")

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-g)
  add_compile_options(-O0)
endif()

add_executable(main ${SRC_FILES})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(main PRIVATE ${SANITIZER_FLAGS} ${PERFORMANCE_FLAGS} ${WARNING_FLAGS})
target_link_options(main PRIVATE ${SANITIZER_FLAGS})
