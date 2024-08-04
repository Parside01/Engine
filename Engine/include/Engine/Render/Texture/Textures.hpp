#ifndef ENGINE_TEXTURES_HPP
#define ENGINE_TEXTURES_HPP

#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>

namespace Engine {
    enum class TextureType : uint8_t {
        Texture2D = 0,
        Texture3D = 0,
    };

    class Texture {
        friend class TextureManager;
    public:
        Texture() = default;
        virtual ~Texture() = default;

        [[nodiscard]] virtual uint32_t GetWidth() const = 0;
        [[nodiscard]] virtual uint32_t GetHeight() const = 0;
        [[nodiscard]] virtual uint32_t GetTextureID() const = 0;
        [[nodiscard]] virtual uint32_t GetTextureHash() const = 0;

        bool operator==(const Texture& other) const { return GetTextureID() == other.GetTextureID() || GetTextureHash() == other.GetTextureHash(); }
    };


    // class Texture2D : public Texture {
    // public:
    //     Texture2D() = default;
    //     Texture2D(const std::string& path);
    //     virtual ~Texture2D() { delete mTextureData; }
    //
    //     virtual bool Resize(uint32_t width, uint32_t height);
    //
    //     virtual uint32_t GetHeight() const override { return mHeight; }
    //     virtual uint32_t GetWidth() const override { return mWidth; }
    //     virtual uint32_t GetChannels() const { return mChannels; }
    //
    //     virtual uint32_t GetTextureHash() const override { return mTextureHash; }
    //     virtual uint32_t GetTextureID() const override { return mTextureID; }
    //
    //     virtual  u_char* GetTextureData() const { return mTextureData; }
    // protected:
    //     u_char* mTextureData;
    //
    //     uint32_t mWidth;
    //     uint32_t mHeight;
    //     uint32_t mChannels;
    //
    //     uint32_t mTextureHash;
    //     uint32_t mTextureID;

    // };
    class Texture2D {
        friend class TextureManager;
        friend class TextureAtlas;
    public:
        ~Texture2D() = default;

        uint32_t Width;
        uint32_t Height;
        uint32_t Channels;

        uint32_t TextureHash;

        bool operator==(Texture2D& other) { return TextureHash == other.TextureHash; }
    private:
        Scope<u_char[]> TextureData;
    };

    class Texture3D : public Texture {
    public:
        virtual ~Texture3D() = default;

        virtual uint32_t GetDepth() const = 0;
    };
}

#endif //ENGINE_TEXTURES_HPP
