#ifndef TEXTURE_OPENGL_HPP
#define TEXTURE_OPENGL_HPP
#include "Engine/Render/Texture.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Engine {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        [[nodiscard]] virtual uint32_t GetWidth() const override { return m_Width; }
        [[nodiscard]] virtual uint32_t GetHeight() const override { return m_Height; };

        virtual void SetData(void* data, uint32_t size) override;
        virtual void Bind(uint32_t slot = 0) const override;

        uint32_t GetTextureID() const override { return m_RendererID; }

        virtual bool operator==(const Texture& other) const override;
    private:
        std::string m_TexturePath;
        int32_t m_Width;
        int32_t m_Height;
        uint32_t m_RendererID;

        GLenum m_InternalFormat;
        GLenum m_DataFormat;
    };
}

#endif //TEXTURE_HPP
