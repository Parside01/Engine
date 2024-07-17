#ifndef ENGINE_PROFILING_TIMER_HPP
#define ENGINE_PROFILING_TIMER_HPP

#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    namespace Benchmark
    {
        class ProfilingTimer {
        public: 
            ProfilingTimer(const char* name);
            ~ProfilingTimer(); 

            void Stop();
        private: 
            const char* m_Name;
            std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
            bool m_Stopped{false};
        };
    } // namespace BenBenchmark
    
} // namespace Engine


#endif