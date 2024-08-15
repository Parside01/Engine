#ifndef ENGINE_TEXTUREATLAS_OPENGL_HPP
#define ENGINE_TEXTUREATLAS_OPENGL_HPP
#ifdef ENGINE_API_OPENGL

#include <Engine/Render/Texture/TextureAtlas.hpp>
#include <Engine/log/Log.hpp>

namespace Engine {

    class OpenGLTextureAtlas : public TextureAtlas {
    public:
        OpenGLTextureAtlas(TextureTarget target, uint32_t width, uint32_t height, uint32_t channels);

        ~OpenGLTextureAtlas() override;

        virtual void Bind(uint32_t slot = 0) override;

        virtual uint32_t GetRendererID() const override { return mRendererID; }

        virtual void Init() override;
    private:
        void InitTexture2D();

        virtual void UpdateAtals() override;
    private:
        uint32_t mRendererID;
        uint32_t mInternalFormat;
        uint32_t mFormat;
    };

}

#endif
#endif // ENGINE_TEXTUREATLAS_OPENGL_HPP
