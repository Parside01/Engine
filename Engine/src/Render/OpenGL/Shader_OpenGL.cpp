#include "Engine/Render/OpenGL/Shader_OpenGL.hpp"

#include <GL/glew.h>
#include <GL/gl.h> 

#include "Engine/log/Log.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
    
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar *source = (const GLchar *)vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteShader(vertexShader);

            EG_CORE_ERROR("Error compile vertex shader: {0}", infoLog.data());
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = (const GLchar *)fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
    
            glDeleteShader(vertexShader);

            EG_CORE_ERROR("Error compile fragment shader: {0}", infoLog.data());
            return;
        }

        m_RendererID = glCreateProgram();

        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);

        glLinkProgram(m_RendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);
            
            glDeleteProgram(m_RendererID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            EG_CORE_ERROR("Error link shader: {0}", infoLog.data());
            return;
        }

        glDetachShader(m_RendererID, vertexShader);
        glDetachShader(m_RendererID, fragmentShader);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& vec) {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }

    void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& vec) {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void OpenGLShader::SetUniformInt(const std::string &name, int value) {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }
} // namespace Engine
