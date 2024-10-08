#ifndef ENGINE_LOG_HPP 
#define ENGINE_LOG_HPP

// #include "../Core.hpp"

#include "Engine/Core.hpp"
#include "Engine/events/Event.hpp"

#include "Engine/benchmark/Benchmark.hpp"

#include "spdlog/spdlog.h"

namespace Engine
{
    class ENGINE_API Log {
    public:
        
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
} // namespace Engine


// Типа логирование для разных типов движка. 
template<>
struct fmt::formatter<Engine::Event> : fmt::formatter<std::string> {
    auto format(const Engine::Event& event, format_context &ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "{}", event.ToString());
    }
};


// Core log macros
#define EG_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EG_CORE_INFO(...)  ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EG_CORE_WARN(...)  ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EG_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EG_CORE_FATAL(...) ::Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define EG_TRACE(...)      ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EG_INFO(...)       ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define EG_WARN(...)       ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EG_ERROR(...)      ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define EG_FATAL(...)      ::Engine::Log::GetClientLogger()->fatal(__VA_ARGS__)


#endif