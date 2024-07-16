#ifndef ENGINE_SHADER_OPENGL_HPP
#define ENGINE_SHADER_OPENGL_HPP

#include <GL/glew.h>

#include "Engine/engine_precompile_headers.hpp"

#include "Engine/Render/Shader.hpp"
#include <glm/glm.hpp>

namespace Engine
{
    class OpenGLShader : public Shader {
    public: 
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        explicit OpenGLShader(const std::string& path);
        virtual ~OpenGLShader();

        [[nodiscard]] virtual const std::string& GetName() const override { return m_Name; };

        virtual void Bind() const override;
        virtual void Unbind() const override; 

        virtual void SetMat4(const std::string& name, const glm::mat4& mat) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3& vec) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& vec) override;
        virtual void SetInt(const std::string& name, int value) override; 

    public: 

        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
        void SetUniformFloat4(const std::string& name, const glm::vec4& vec); 
        void SetUniformFloat3(const std::string& name, const glm::vec3& vec);
        void SetUniformInt(const std::string& name, int value);

    private:

        std::string ReadFromFile(const std::string& path);
        std::unordered_map<GLenum, std::string> ProcessSource(const std::string& source);
        void CompileShader(const std::unordered_map<GLenum, std::string>& shaders);

    private:
        std::string m_Name;
        uint32_t m_RendererID;
    };
} // namespace Engine


#endif