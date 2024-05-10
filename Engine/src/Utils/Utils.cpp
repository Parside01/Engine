#include "Engine/Utils.hpp"

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
} // namespace Utils
