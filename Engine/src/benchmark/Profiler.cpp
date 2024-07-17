#include "Engine/engine_precompile_headers.hpp"
#include "Engine/log/Log.hpp"

namespace Engine
{
    namespace Benchmark
    {
        void Profiler::BeginSession(const std::string& name, const std::string& path) {
            m_OutStream.open(path);
            if (!m_OutStream.is_open()) {
                EG_CORE_ERROR("Failed to open {0}", path);
            }

            WriteHeader();
        }

        void Profiler::EndSession() {
            WriteFooter();
            m_OutStream.close();
            delete m_Session;
            m_Session = nullptr;
        }

        void Profiler::WriteHeader() {
            m_OutStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutStream.flush();
        }

        void Profiler::WriteFooter() {
            m_OutStream << "]}";
            m_OutStream.flush();
        }

        void Profiler::WriteProfile(const ProfilingResult& res) {
            if (m_ProfilingCount++ > 0) m_OutStream << ",";

            std::string name = res.Name;
            std::replace(std::begin(name), std::end(name), '"', '\'');
            m_OutStream << std::setprecision(3) << std::fixed;
            m_OutStream << "{"; 
            m_OutStream << "\"cat\":\"function\",";
            m_OutStream << "\"dur\":" << res.Duration.count() << ',';
            m_OutStream << "\"name\":\"" << name << "\","; 
            m_OutStream << "\"ph\":\"X\","; 
            m_OutStream << "\"pid\":0,"; 
            m_OutStream << "\"tid\":" << res.ThreadID << ','; 
            m_OutStream << "\"ts\":" << res.Start.count();
            m_OutStream << "}";

            m_OutStream.flush();
        }

        
    } // namespace Profiling
    
} // namespace Engine
