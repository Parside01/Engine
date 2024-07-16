#include "Engine/Render/OpenGL/Shader_OpenGL.hpp"

#include <GL/glew.h>
#include <GL/gl.h> 

#include "Engine/log/Log.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
    static GLenum GetShaderType(const std::string& type) {
        if (type == "Vertex" || type == "vertex") return GL_VERTEX_SHADER;
        if (type == "Fragment" || type == "fragment") return GL_FRAGMENT_SHADER;
        EG_CORE_ERROR("Неподдерживаемый тип шейдера --- {0}", type);
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& path) {
        const std::string source = ReadFromFile(path);
        const std::unordered_map<GLenum, std::string> shaderSources = ProcessSource(source);
        CompileShader(shaderSources);

        auto lastSlash = path.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = path.rfind('.');
        auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
        m_Name = path.substr(lastSlash, count);
    }

    void OpenGLShader::CompileShader(const std::unordered_map<GLenum, std::string>& shaders) {
        GLint program = glCreateProgram();
        EG_CORE_ASSERT(shaders.size() <= 2, "Пока поддерживается только 2 шейдера");
        std::array<GLenum, 2> shadersID;
        size_t shadersIndex{0};
        for (const auto& item : shaders) {
            GLenum type = item.first;
            const std::string source = item.second;

            GLuint shader = glCreateShader(type);

            const GLchar *sourceCh = source.c_str();
            glShaderSource(shader, 1, &sourceCh, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                EG_CORE_ERROR("Error compile shader: {0}", infoLog.data());
                break;
            }

            glAttachShader(program, shader);
            shadersID[shadersIndex++] = shader;
        }
        glLinkProgram(program);
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            for (const auto& id : shadersID)
                glDeleteShader(id);

            EG_CORE_ERROR("Error link shader: {0}", infoLog.data());
            EG_CORE_ASSERT(false, "Ошибка компановки шейдера");
            return;
        }
        for (const auto& id : shadersID)
            glDetachShader(m_RendererID, id);
        m_RendererID = program;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::ProcessSource(const std::string &source) {
        std::unordered_map<GLenum, std::string> shaderSources;
        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            EG_CORE_ASSERT(eol != std::string::npos, "Синтаксическая ошибка в файле");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            EG_CORE_ASSERT(GetShaderType(type), "Неподдерживаемый тип шейдера");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            EG_CORE_ASSERT(nextLinePos != std::string::npos, "Синтаксическая ошибка в файле");
            pos = source.find(typeToken, nextLinePos);

            shaderSources[GetShaderType(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }


    std::string OpenGLShader::ReadFromFile(const std::string& path) {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        std::string result;

        if (!file) EG_CORE_ERROR("Не удалось открыть файл с шейдером по маршруту {0}", path);

        file.seekg(0, std::ios::end);
        result.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&result[0], result.size());
        file.close();
        return result;
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        std::unordered_map<GLenum, std::string> source;
        source[GL_VERTEX_SHADER] = vertexSrc;
        source[GL_FRAGMENT_SHADER] = fragmentSrc;
        CompileShader(source);
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

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4 &mat) {
        SetUniformMat4(name, mat);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& vec) {
        SetUniformFloat4(name, vec);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& vec) {
        SetUniformFloat3(name, vec);
    }

    void OpenGLShader::SetInt(const std::string& name, int value) {
        SetUniformInt(name, value);
    }

    void OpenGLShader::SetUniformMat4(const std::string &name, const glm::mat4 &matrix)
    {
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
