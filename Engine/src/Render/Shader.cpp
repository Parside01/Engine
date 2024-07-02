#include "Engine/Render/Shader.hpp"
#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/RendererAPI.hpp"
#include "Engine/Render/OpenGL/Shader_OpenGL.hpp"

namespace Engine
{
    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        EG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::Add(const Ref<Shader> &shader) {
        auto& name = shader->GetName();
        Add(name, shader);
    }
    
    void ShaderLibrary::Add(const std::string &name, const Ref<Shader> &shader) {
        if (IsExist(name)) EG_CORE_ERROR("Шейдер {0} не найден", name);
        m_Shaders[name] = shader;
    }

    bool ShaderLibrary::IsExist(const std::string &name) const {
        return m_Shaders.find(name) != m_Shaders.end();
    }


    Ref<Shader> ShaderLibrary::Get(const std::string &name) {
        if (IsExist(name)) EG_CORE_ERROR("Шейдер {0} не найден", name);
        return m_Shaders[name];
    }

    Ref<Shader> ShaderLibrary::LoadFromFile(const std::string &path) {
        auto shader = Shader::Create(path);
        Add(shader);
        return shader;
    }


    Ref<Shader> ShaderLibrary::LoadFromFile(const std::string &name, const std::string &path) {
        auto shader = Shader::Create(path);
        Add(name, shader);
        return shader;
    }


    Ref<Shader> Shader::Create(const std::string& path) {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(path);
        }

        EG_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace Engine
