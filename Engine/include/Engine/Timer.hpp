#ifndef ENGINE_TIMER_HPP
#define ENGINE_TIMER_HPP

#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    class Timer {
    public:
        Timer(const char* name) : m_Name(name), m_Stopped(false) {
            m_StartTime = std::chrono::high_resolution_clock::now();
        }

        ~Timer() {
            if (!m_Stopped) Stop();
        }

        void Stop() {
            auto endTime = std::chrono::high_resolution_clock::now();
            uint32_t start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTime).time_since_epoch().count();
            uint32_t end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTime).time_since_epoch().count();

            m_Stopped = true; 

            std::cout << m_Name << " : "  << " Duration : " << end - start << "ms" << std::endl;
        }

    private:
        const char* m_Name; 
        std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        bool m_Stopped;
    };
} // namespace Engine


#endif