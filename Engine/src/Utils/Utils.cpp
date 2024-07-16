#include "Engine/Utils.hpp"
#include "Engine/Core.hpp"

namespace Utils
{
    const char* GetAbsolutePath(const char* realPath) {
        char* absolutePath = new char[PATH_MAX];
        realpath(realPath, absolutePath);
        return absolutePath;
    }

    std::string GetAbsolutePath(const std::string& path) {
        return GetAbsolutePath(path.c_str());
    }

    uint32_t GetColor(const glm::vec4& color) {
        return (static_cast<uint32_t>(color.r * 255.0f) << 24) |
               (static_cast<uint32_t>(color.g * 255.0f) << 16) |
               (static_cast<uint32_t>(color.b * 255.0f) << 8) |
               static_cast<uint32_t>(color.a * 255.0f);
    }
} // namespace Utils
