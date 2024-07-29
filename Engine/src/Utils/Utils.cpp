#include "Engine/Utils.hpp"
#include "Engine/Core.hpp"
#include "Engine/log/Log.hpp"

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

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#ifdef __linux__
    #include <cstdlib>
    #include <string>

    std::string FileDialogs::OpenFile(const std::string& filter) {
        std::string command = "zenity --file-selection --file-filter=" + filter;
        command.append(" --title='Open File'");
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) return ""; 

        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            buffer[strcspn(buffer, "\n")] = 0;
            pclose(pipe);
            return buffer;
        }

        pclose(pipe);
        return "";
    }
    
    std::string FileDialogs::SaveFile(const std::string& filter) {
        std::string command = "zenity --file-selection --save --file-filter=" + filter;
        command.append(" --title='Save File'");
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) return "";

        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            buffer[strcspn(buffer, "\n")] = 0;
            pclose(pipe);
            return buffer;
        }

        pclose(pipe);
        return "";
    }

#endif

#ifdef _WIN32
    std::string FileDialogs::OpenFile(const std::string& path) {

    }
    
    std::string FileDialogs::SaveFile(const std::string& path) {
        
    }
#endif
} // namespace Utils
