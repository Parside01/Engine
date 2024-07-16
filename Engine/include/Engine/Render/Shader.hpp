#ifndef ENGINE_SHADER_HPP
#define ENGINE_SHADER_HPP 

#include <string>
#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>

namespace Engine
{
    class Shader {
    public: 
        virtual ~Shader() = default;

        [[nodiscard]] virtual const std::string& GetName() const = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetMat4(const std::string& name, const glm::mat4& mat) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& vec) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& vec) = 0;
        virtual void SetInt(const std::string& name, int value) = 0;

        static Ref<Shader> Create(const std::string& path);
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    class ShaderLibrary {
    public:

        void Add(const Ref<Shader>& shader);
        void Add(const std::string& name, const Ref<Shader>& shader);
        Ref<Shader> Get(const std::string& name);
        Ref<Shader> LoadFromFile(const std::string& path);
        Ref<Shader> LoadFromFile(const std::string& name, const std::string& path);

        bool IsExist(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}


#endif