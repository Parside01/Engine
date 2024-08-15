#ifndef ENGINE_TEXTURES_HPP
#define ENGINE_TEXTURES_HPP

#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>

namespace Engine {

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

    class Texture2D {
        friend class TextureManager;
        friend class TextureAtlas;
    public:
        virtual ~Texture2D() = default;
        bool operator==(Texture2D& other) { return TextureHash == other.TextureHash; }

    protected:
        uint32_t Width;
        uint32_t Height;
        uint32_t Channels;

        uint32_t TextureHash;

        Scope<u_char[]> TextureData; // После добавления в атлас, эта штука удаляется.
    };

    class CubeMap {
        friend class TextureManager;
    public:

        virtual ~CubeMap() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    private:
        std::array<Scope<u_char[]>, 6> mFaces;
        uint32_t mFaceWidth;
        uint32_t mFaceHeight;
        uint32_t mChannelsNum;
        uint32_t mTextureHash;
    };
}

#endif //ENGINE_TEXTURES_HPP
