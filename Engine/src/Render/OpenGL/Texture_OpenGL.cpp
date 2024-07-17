#include "Engine/Render/OpenGL/Texture_OpenGL.hpp"

#include "stb_image.hpp"
#include "Engine/log/Log.hpp"
#include "Engine/Utils.hpp"

#include <filesystem>

namespace Engine {
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, glm::vec4 color)
    : m_Height(height), m_Width(width)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
        uint32_t textureData = Utils::GetColor(color);
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, &textureData);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    OpenGLTexture2D::OpenGLTexture2D(const std::string &path)
    : m_TexturePath(path)
    {
        int x, y, channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(m_TexturePath.c_str(), &x, &y, &channels, 0);

        m_Width = x;
        m_Height = y;

        GLenum internalFormat{0}, dataFormat{0};
        if (channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if (channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        m_InternalFormat = internalFormat; 
        m_DataFormat = dataFormat; 

        EG_CORE_ASSERT(internalFormat & dataFormat, "Format is not supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(0, m_RendererID);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size) {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        EG_CORE_ASSERT(size == m_Width * m_Height * bpp, "Указан не тот размер для текстуры");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

}
