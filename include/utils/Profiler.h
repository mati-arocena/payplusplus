#pragma once

#ifdef PERF_PROFILING

#include <iostream>
#include <chrono>
#include <string>

#define SCOPED_PROF(name) ppp::Profiler timer##__LINE__(name)

namespace ppp
{

class Profiler {
public:
    explicit Profiler(const std::string& name)
        : m_name(name), m_start_time(std::chrono::high_resolution_clock::now()) {}

    ~Profiler() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end_time - m_start_time).count();
        std::cout << "[Profiler] " << m_name << " took " << duration << " ms" << std::endl;
    }

private:
    std::string m_name;
    std::chrono::high_resolution_clock::time_point m_start_time;
};

} // namespace ppp

#else

#define SCOPED_PROF(name)

#endif