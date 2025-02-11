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
        : m_Name(name), m_StartTime(std::chrono::high_resolution_clock::now()) {}

    ~Profiler() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(endTime - m_StartTime).count();
        std::cout << "[Profiler] " << m_Name << " took " << duration << " ms" << std::endl;
    }

private:
    std::string m_Name;
    std::chrono::high_resolution_clock::time_point m_StartTime;
};

} // namespace ppp

#else

#define SCOPED_PROF(name)

#endif