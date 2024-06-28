#ifndef ENGINE_SHADER_HPP
#define ENGINE_SHADER_HPP 

#include <string>

namespace Engine
{
    class Shader {
    public: 
        virtual ~Shader() = default; 

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Shader* Create(const std::string& path);
        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}


#endif