#include "Engine/Render/Shader.hpp"
#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/RendererAPI.hpp"
#include "Engine/Render/OpenGL/Shader_OpenGL.hpp"

namespace Engine
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        EG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Shader* Shader::Create(const std::string& path) {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(path);
        }

        EG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Engine
