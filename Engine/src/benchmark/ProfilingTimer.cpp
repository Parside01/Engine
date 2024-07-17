#include "Engine/benchmark/ProfilingTimer.hpp"

namespace Engine
{
    namespace Benchmark
    {
        ProfilingTimer::ProfilingTimer(const char* name) : m_Name(name), m_StartTime(std::chrono::high_resolution_clock::now()) {}
        ProfilingTimer::~ProfilingTimer() {
            if (!m_Stopped) Stop();
        }

        void ProfilingTimer::Stop() {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();

            uint32_t start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTime).time_since_epoch().count();
            uint32_t end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTime).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            auto duration = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch();
            Profiler::Get().WriteProfile({m_Name, duration.count(), m_StartTime.time_since_epoch().count(), threadID});

            m_Stopped = true;
        }
    } // namespace Benchmark
    
} // namespace Engine
