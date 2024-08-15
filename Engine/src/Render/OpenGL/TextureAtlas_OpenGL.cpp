#ifdef ENGINE_API_OPENGL

#include <Engine/Render/OpenGL/OpenGLUtils.hpp>
#include <Engine/Render/OpenGL/TextureAtlas_OpenGL.hpp>
#include <Engine/Utils.hpp>
#include <GL/glew.h>


namespace Engine {

    OpenGLTextureAtlas::OpenGLTextureAtlas(TextureTarget target, uint32_t width, uint32_t height, uint32_t channels)
        : TextureAtlas(target, width, height, channels) {
        EG_PROFILE_FUNC();
        auto [format, internalFormat] = OpenGLUtils::GetOpenGLFormatFromChannels(channels);
        if (!format || !internalFormat) {
            EG_CORE_ERROR("Неподдерживаемое количество каналов в изображении, количество каналов {0}", channels);
            EG_CORE_ASSERT(false);
        }

        mFormat = format;
        mInternalFormat = internalFormat;
    }

    void OpenGLTextureAtlas::Init() {
        switch (mSpecefication->mTarget) {
            case TextureTarget::TEXTURE2D:
                InitTexture2D();
                break;
            case TextureTarget::TEXTURE_CUBE_MAP:
                EG_CORE_ASSERT(false);
                break;
        }
    }

    void OpenGLTextureAtlas::InitTexture2D() {
        glCreateTextures(OpenGLUtils::TextureTargetToOpenGL(mSpecefication->mTarget), 1, &mRendererID);
        glTextureStorage2D(mRendererID, 1, mInternalFormat, mSpecefication->mWidth, mSpecefication->mHeight);
        for (const auto& [name, value] : mSpecefication->mParams) {
            glTextureParameteri(mRendererID, OpenGLUtils::TextureParamNameToOpenGL(name), OpenGLUtils::TextureParamValueToOpenGL(value));
        }
    }

    void OpenGLTextureAtlas::UpdateAtals() {
        EG_PROFILE_FUNC();
        glTextureSubImage2D(mRendererID, 0, 0, 0, mSpecefication->mWidth, mSpecefication->mHeight, mFormat,
                            GL_UNSIGNED_BYTE, mData.get());
    }

    OpenGLTextureAtlas::~OpenGLTextureAtlas() {
        glDeleteTextures(1, &mRendererID);
    }

    void OpenGLTextureAtlas::Bind(uint32_t slot) {
        mTextureSlot = slot;
        glBindTextureUnit(slot, mRendererID);
    }
}
#endif
