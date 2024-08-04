#ifdef ENGINE_API_OPENGL

#include "Engine/Render/OpenGL/Texture2D_OpenGL.hpp"
#include "stb_image.hpp"
#include <GL/glew.h>
#include "Engine/log/Log.hpp"
#include "Engine/benchmark/Benchmark.hpp"

namespace Engine {

#if 0

    u_char* Texture2D_OpenGL::GetDataFromImage(const std::filesystem::path& path) {
        EG_PROFILE_FUNC();

        int x, y, channels;
        stbi_set_flip_vertically_on_load(1);
        u_char* data = stbi_load(path.string().c_str(), &x, &y, &channels, 0);

        if (!data) {
            EG_CORE_WARN("Не получилось прочитать из файла {0}", path.string());
            EG_CORE_ASSERT(false);
        }

        switch (channels)
        {
        case 1:
            mFormat = GL_R;
            mInternalFormat = GL_R8;
            break;
        case 2:
            mFormat = GL_RG;
            mInternalFormat = GL_RG8;
            break;
        case 3:
            mFormat = GL_RGB;
            mInternalFormat = GL_RGB8;
            break;
        case 4:
            mFormat = GL_RGBA;
            mInternalFormat = GL_RGBA8;
            break;
        default:
            stbi_image_free(data);
            EG_CORE_ERROR("Неподдерживаемое количество каналов в изображении, количество каналов {0}", channels);
            EG_CORE_ASSERT(false);
            break;
        }

        mWidth = x; mHeight = y;
        uint32_t dataSize = mWidth * mHeight * channels;
        uint32_t textureHash = std::hash<std::string_view>()(std::string_view(reinterpret_cast<const char*>(data), dataSize));
        mTextureHash = textureHash;
        return data;
    }

    void Texture2D_OpenGL::CreateTextureAndSetData(const u_char *textureData) {
        EG_PROFILE_FUNC();

        glCreateTextures(GL_TEXTURE_2D, 1, &mTextureID);

        glTextureStorage2D(mTextureID, 1, mInternalFormat, mWidth, mHeight);

        glTextureParameteri(mTextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(mTextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(mTextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(mTextureID, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glTextureParameteri(mTextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(mTextureID, 0, 0, 0, mWidth, mHeight, mFormat, GL_UNSIGNED_BYTE, textureData);
    }

    Texture2D_OpenGL::Texture2D_OpenGL(const std::filesystem::path &path) {
        EG_PROFILE_FUNC();

        u_char* textureData = GetDataFromImage(path);
        CreateTextureAndSetData(textureData);
        stbi_image_free(textureData);
    }

    Texture2D_OpenGL::Texture2D_OpenGL(uint32_t width, uint32_t height, const u_char *data)
        : mFormat(GL_RGBA), mInternalFormat(GL_RGBA8)
    {
        EG_PROFILE_FUNC();

        mHeight = height;
        mWidth = width;
        CreateTextureAndSetData(data);
    }

    Texture2D_OpenGL::~Texture2D_OpenGL() {
        glDeleteTextures(1, &mTextureID);
    }

    void Texture2D_OpenGL::Bind(uint32_t slot) const {
        glBindTexture(GL_TEXTURE_2D, mTextureID);
    }
    void Texture2D_OpenGL::Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
#endif
}

#endif
