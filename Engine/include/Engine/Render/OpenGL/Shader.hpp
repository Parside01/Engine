#ifndef ENGINE_SHADER_HPP
#define ENGINE_SHADER_HPP

#include "Engine/engine_precompile_headers.hpp"

#include <glm/glm.hpp>

namespace Engine
{
    class Shader {
    public: 
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);


    private:
        uint32_t m_RendererID;
    };
} // namespace Engine


#endif