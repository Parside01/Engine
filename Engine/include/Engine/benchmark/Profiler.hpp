#ifndef ENGINE_PROFILING_HPP
#define ENGINE_PROFILING_HPP

#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    namespace Benchmark
    {
        struct ProfilingResult {
            const char* Name; 
            int64_t Duration;
            int64_t Start;
            uint32_t ThreadID;
        };

        struct ProfilingSession {
            const char* Name;
        };

        class Profiler {
        public: 

            Profiler() : m_Session(nullptr), m_ProfilingCount(0) {}
            ~Profiler() {
                EndSession();
            }
            void BeginSession(const std::string& name, const std::string& path = "profile.json");
            void EndSession();
            void WriteProfile(const ProfilingResult& res);
            void WriteHeader();
            void WriteFooter();

            static Profiler& Get() {
                static Profiler instance;
                return instance;
            }

        private:

            ProfilingSession* m_Session;
            std::ofstream m_OutStream; 
            int m_ProfilingCount;
        };
    } // namespace Benchmark
} // namespace Engine


#endif 
