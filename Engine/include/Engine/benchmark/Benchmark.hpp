#ifndef ENGINE_BENCHMARK_HPP
#define ENGINE_BENCHMARK_HPP

    #include "Engine/engine_precompile_headers.hpp"
    #ifdef ENGINE_PROFILING
        #define EG_PROFILE_BEGIN_SESSION(name, path) ::Engine::Benchmark::Profiler::Get().BeginSession(name, path)
        #define EG_PROFILE_END_SESSION() ::Engine::Benchmark::Profiler::Get().EndSession()
        #define EG_PROFILE_SCOPE(name) ::Engine::Benchmark::ProfilingTimer timer##__LINE__(name)
        #define EG_PROFILE_FUNC() EG_PROFILE_SCOPE(__PRETTY_FUNCTION__)
    #else 
        #define EG_PROFILE_BEGIN_SESSION(name, path) 
        #define EG_PROFILE_END_SESSION()
        #define EG_PROFILE_FUNC() 
        #define EG_PROFILE_SCOPE(name)
    #endif

#endif