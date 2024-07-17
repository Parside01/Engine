#include "Engine/Timer.hpp"

namespace Engine
{

    Timer::Timer(const char* name) : m_Name(name), m_Stopped(false) {
            m_StartTime = std::chrono::high_resolution_clock::now();
    }

    Timer::~Timer() {
        if (!m_Stopped) Stop();
    }

    void Timer::Stop() {
        auto endTime = std::chrono::high_resolution_clock::now();
        uint32_t start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTime).time_since_epoch().count();
        uint32_t end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTime).time_since_epoch().count();

        m_Stopped = true;   
        float duration = (end - start) * 0.001f;

        std::cout << m_Name << " : "  << " Duration : " << duration << "ms" << std::endl;
    }
} // namespace Engine
