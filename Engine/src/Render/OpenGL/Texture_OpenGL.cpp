#include "Engine/Render/OpenGL/Texture_OpenGL.hpp"

#include "stb_image.hpp"
#include "Engine/log/Log.hpp"

#include <GL/glew.h>
#include <filesystem>

namespace Engine {
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

        EG_CORE_ASSERT(internalFormat & dataFormat, "Format is not supported");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(0, m_RendererID);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_RendererID);
    }



}
