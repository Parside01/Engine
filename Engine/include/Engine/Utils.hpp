#ifndef ENGINE_BASE_HPP
#define ENGINE_BASE_HPP

    #include "Engine/engine_precompile_headers.hpp"
    #include <glm/glm.hpp>

    #if defined(__linux__)
        #include "csignal"
        #define EG_DEBUG_BREAK() raise(SIGTRAP)
    #endif


    // Надо будет перенести в другое место, а то не смотрится вообще.
    #define EG_GET_ABSOLUTE_PATH(relPath) ({ \
        char absolutePath[PATH_MAX]; \
        realpath(relPath, absolutePath); \
        (const char*)absolutePath; \
    })

    #define BIT(x) (1 << x)

    #define EG_BINDEVENT(fn) [this](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }

    #define EG_EXPAND_MACRO(x) x
    #define EG_STRINGIFY_MACRO(x) #x

    #define EG_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { EG##type##ERROR(msg, __VA_ARGS__); EG_DEBUG_BREAK(); } }
	#define EG_INTERNAL_ASSERT_WITH_MSG(type, check, ...) EG_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define EG_INTERNAL_ASSERT_NO_MSG(type, check) EG_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", EG_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define EG_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define EG_INTERNAL_ASSERT_GET_MACRO(...) EG_EXPAND_MACRO( EG_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EG_INTERNAL_ASSERT_WITH_MSG, EG_INTERNAL_ASSERT_NO_MSG) )

	#define EG_ASSERT(...) EG_EXPAND_MACRO( EG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define EG_CORE_ASSERT(...) EG_EXPAND_MACRO( EG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#ifdef ENGINE_API_OPENGL
#include <signal.h>
#include <GL/glew.h>
    static void GLClearError() {
        while (glGetError() != GL_NO_ERROR) {}
    }

    static bool GLLogCall(const char* function, const char* file, int line) {
        while (const GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
            return false;
        }
        return true;
    }

#define GLCall(x) ({ \
GLClearError(); \
x; \
assert(GLLogCall(#x, __FILE__, __LINE__)); \
})

#endif

    namespace Utils {
        const char* GetAbsolutePath(const char* relPath);
        std::string GetAbsolutePath(const std::string& path);
        uint32_t GetColor(const glm::vec4& color);

        class FileDialogs {
        public:
            static std::string OpenFile(const std::string& path);
            static std::string SaveFile(const std::string& path);
        };
        inline uint32_t HashUCharData(u_char* data, size_t dataSize) {
            return std::hash<std::string_view>()(std::string_view(reinterpret_cast<const char*>(data), dataSize));
        }
    }
#endif