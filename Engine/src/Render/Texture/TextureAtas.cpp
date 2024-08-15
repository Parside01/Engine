#include <stb_image.hpp>

#include "Engine/Render/Texture/TextureAtlas.hpp"
#include <stb_image_write.hpp>
#include <Engine/log/Log.hpp>


namespace Engine {
    TextureAtlas::TextureAtlas(TextureTarget target, uint32_t width, uint32_t height, uint32_t channels)
        : mData(new u_char[width * height * channels]), mSpecefication(std::make_unique<TextureSpec>()) {
        mSpecefication->mHeight = height;
        mSpecefication->mWidth = width;
        mSpecefication->mChannelsNum = channels;
        mSpecefication->mParams = {
            {TextureParamName::TEXTURE_MIN_FILTER, TextureParamValue::LINEAR},
            {TextureParamName::TEXTURE_MAG_FILTER, TextureParamValue::LINEAR},
            {TextureParamName::TEXTURE_WRAP_R, TextureParamValue::REPEAT},
            {TextureParamName::TEXTURE_WRAP_S, TextureParamValue::REPEAT},
            {TextureParamName::TEXTURE_WRAP_T, TextureParamValue::REPEAT},
        };
    }

    TextureAtlas::TextureAtlas(const TextureSpec& spec)
        : mData(new u_char[spec.mHeight * spec.mWidth * spec.mChannelsNum]), mSpecefication(std::make_unique<TextureSpec>(spec)) {}

    void TextureAtlas::AddTexture2D(const Ref<Texture2D> &texture) {
        EG_PROFILE_FUNC();

        // Если она уже есть то не добавляем.
        if (mTextureCoords.find(texture->TextureHash) != mTextureCoords.end())
            return;

        glm::vec4 textureCoords(
            mxOffset / static_cast<float>(mSpecefication->mWidth),
            myOffset / static_cast<float>(mSpecefication->mHeight),
            (mxOffset + texture->Width) / static_cast<float>(mSpecefication->mWidth),
            (myOffset + texture->Height) / static_cast<float>(mSpecefication->mHeight)
        );
        mTextureCoords[texture->TextureHash] = textureCoords;

        for (uint32_t y{0}; y < texture->Height; ++y) {
            for (uint32_t x{0}; x < texture->Width; ++x) {
                uint32_t atlasIndex = (myOffset + y) * mSpecefication->mWidth * mSpecefication->mChannelsNum + (mxOffset + x) * mSpecefication->mChannelsNum;
                uint32_t textureIndex = y * texture->Width * texture->Channels + x * texture->Channels;
                for (int c = 0; c < texture->Channels; ++c) {
                    mData[atlasIndex + c] = texture->TextureData[textureIndex + c];
                }
            }
        }
        mxOffset += texture->Width;
        if (mxOffset >= mSpecefication->mWidth) {
            mxOffset = 0;
            myOffset += texture->Height;
        }
        texture->TextureData.reset();

        UpdateAtals();
    }

    bool TextureAtlas::WriteAtlasInFile(const std::string &path) const {
        EG_PROFILE_FUNC();
        return stbi_write_png(path.c_str(), mSpecefication->mWidth, mSpecefication->mHeight, mSpecefication->mChannelsNum, mData.get(), mSpecefication->mWidth * mSpecefication->mChannelsNum);
    }
}
