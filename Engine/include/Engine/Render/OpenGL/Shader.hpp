#ifndef ENGINE_SHADER_HPP
#define ENGINE_SHADER_HPP

#include "Engine/engine_precompile_headers.hpp"


namespace Engine
{
    class Shader {
    public: 
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
    private:
        uint32_t m_RenderID;
    };
} // namespace Engine


#endif