#include <stb_image.hpp>

#include "Engine/Render/Texture/TextureAtlas.hpp"
#include <stb_image_write.hpp>
#include <Engine/log/Log.hpp>


namespace Engine {
    TextureAtlas::TextureAtlas(uint32_t width, uint32_t height, uint32_t channels)
        : mData(new u_char[width * height * channels]), mHeight(height), mWidth(width), mChannels(channels) {
    }

    void TextureAtlas::AddTexture(const Ref<Texture2D> &texture) {
        EG_PROFILE_FUNC();

        // Если она уже есть то не добавляем.
        if (mTextureCoords.find(texture->TextureHash) != mTextureCoords.end())
            return;

        glm::vec4 textureCoords(
            mxOffset / static_cast<float>(mWidth),
            myOffset / static_cast<float>(mHeight),
            (mxOffset + texture->Width) / static_cast<float>(mWidth),
            (myOffset + texture->Height) / static_cast<float>(mHeight)
        );
        mTextureCoords[texture->TextureHash] = textureCoords;

        for (uint32_t y{0}; y < texture->Height; ++y) {
            for (uint32_t x{0}; x < texture->Width; ++x) {
                uint32_t atlasIndex = (myOffset + y) * mWidth * mChannels + (mxOffset + x) * mChannels;
                uint32_t textureIndex = y * texture->Width * texture->Channels + x * texture->Channels;
                for (int c = 0; c < texture->Channels; ++c) {
                    mData[atlasIndex + c] = texture->TextureData[textureIndex + c];
                }
            }
        }
        mxOffset += texture->Width;
        if (mxOffset >= mWidth) {
            mxOffset = 0;
            myOffset += texture->Height;
        }
        texture->TextureData.reset();

        UpdateAtals();
    }

    bool TextureAtlas::WriteAtlasInFile(const std::string &path) const {
        EG_PROFILE_FUNC();
        return stbi_write_png(path.c_str(), mWidth, mHeight, mChannels, mData.get(), mWidth * mChannels);
    }
}
