#include "Engine/Render/OpenGL/TextureAtlas_OpenGL.hpp"

namespace Engine {
#ifdef ENGINE_API_OPENGL
    static std::pair<uint32_t, uint32_t> GetFormatFromChannels(uint32_t channels) {
        std::pair<uint32_t, uint32_t> res(0, 0);
        switch (channels) {
            case 1:
                res.first = GL_R;
                res.second = GL_R8;
                break;
            case 2:
                res.first = GL_RG;
                res.second = GL_RG8;
                break;
            case 3:
                res.first = GL_RGB;
                res.second = GL_RGB8;
                break;
            case 4:
                res.first = GL_RGBA;
                res.second = GL_RGBA8;
                break;
            default:
                break;
        }
        return res;
    }

    void OpenGLTextureAtlas::Init() {
        glCreateTextures(GL_TEXTURE_2D, 1, &mRendererID);

        glTextureStorage2D(mRendererID, 1, mInternalFormat, mWidth, mHeight);

        glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glTextureParameteri(mRendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void OpenGLTextureAtlas::UpdateAtals() {
        EG_PROFILE_FUNC();
        glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, mFormat, GL_UNSIGNED_BYTE, mData.get());
    }
    OpenGLTextureAtlas::OpenGLTextureAtlas(uint32_t width, uint32_t height, uint32_t channels)
        : TextureAtlas(width, height, channels)
    {
        EG_PROFILE_FUNC();
        auto [format, internalFormat] = GetFormatFromChannels(channels);
        if (!format || !internalFormat) {
            EG_CORE_ERROR("Неподдерживаемое количество каналов в изображении, количество каналов {0}", channels);
            EG_CORE_ASSERT(false);
        }

        mFormat = format;
        mInternalFormat = internalFormat;
    }

    OpenGLTextureAtlas::~OpenGLTextureAtlas() {
        glDeleteTextures(1, &mRendererID);
    }

    void OpenGLTextureAtlas::Bind(uint32_t slot) {
        mTextureSlot = slot;
        glBindTextureUnit(slot, mRendererID);
    }

#endif
}
