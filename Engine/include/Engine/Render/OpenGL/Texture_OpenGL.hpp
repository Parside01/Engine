#ifndef TEXTURE_OPENGL_HPP
#define TEXTURE_OPENGL_HPP
#include "Engine/Render/Texture.hpp"

namespace Engine {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        [[nodiscard]] virtual uint32_t GetWidth() const override { return m_Width; }
        [[nodiscard]] virtual uint32_t GetHeight() const override { return m_Height; };

        virtual void Bind(uint32_t slot = 0) const override;
    private:
        std::string m_TexturePath;
        int32_t m_Width;
        int32_t m_Height;
        uint32_t m_RendererID;
    };
}

#endif //TEXTURE_HPP
