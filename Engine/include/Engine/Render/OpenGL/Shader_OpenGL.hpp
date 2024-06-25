#ifndef ENGINE_SHADER_OPENGL_HPP
#define ENGINE_SHADER_OPENGL_HPP

#include "Engine/engine_precompile_headers.hpp"

#include "Engine/Render/Shader.hpp"
#include <glm/glm.hpp>

namespace Engine
{
    class OpenGLShader : public Shader {
    public: 
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override; 

        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
        void SetUniformFloat4(const std::string& name, const glm::vec4& vec); 
        void SetUniformFloat3(const std::string& name, const glm::vec3& vec);
        void SetUniformInt(const std::string& name, int value);
    private:
        uint32_t m_RendererID;
    };
} // namespace Engine


#endif