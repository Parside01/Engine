#ifndef ENGINE_TIMER_HPP
#define ENGINE_TIMER_HPP

#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    class Timer {
    public:
        Timer(const char* name);
        ~Timer();

        void Stop();

    private:
        const char* m_Name; 
        std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        bool m_Stopped;
    };
} // namespace Engine


#endif