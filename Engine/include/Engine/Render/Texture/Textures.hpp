#ifndef ENGINE_TEXTURES_HPP
#define ENGINE_TEXTURES_HPP

#include <Engine/engine_precompile_headers.hpp>
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
        bool operator==(Texture2D& other) { return mTextureHash == other.mTextureHash; }

        uint32_t mWidth;
        uint32_t mHeight;
        uint32_t mChannelsNum;

        uint32_t mTextureHash;

        Scope<u_char[]> mTextureData; // После добавления в атлас, эта штука удаляется.
    };

    // Эта штука не храниться в атласе, так что аккуратно.
    class CubeMap {
        friend class TextureManager;
    public:
        virtual ~CubeMap() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint32_t GetTextureID() const = 0;

    protected:
        std::array<Ref<Texture2D>, 6> mFaces;
    };
}

#endif //ENGINE_TEXTURES_HPP
