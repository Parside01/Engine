#ifndef ENGINE_TEXTURE_SYSTEM_SKETCH_HPP
#define ENGINE_TEXTURE_SYSTEM_SKETCH_HPP

#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    enum class TextureType : uint8_t {
        Texture2D = 0, 
        Texture3D = 0,
    }; 

    class Texture {
        friend class TextureManager;
    public:
        Texture();
        virtual ~Texture() = default;

        [[nodiscard]] virtual uint32_t GetWidth() const = 0;
        [[nodiscard]] virtual uint32_t GetHeight() const = 0;
        [[nodiscard]] virtual uint32_t GetTextureID() const = 0;
        [[nodiscard]] virtual uint32_t GetTextureHash() const = 0;

    private:
        virtual void Bind(int slot = 0) const = 0;
        virtual void Unbind() const = 0;
    };


    class Texture2D : public Texture {
    public:
        Texture2D();
        virtual ~Texture2D() = default;
    };

    class Texture3D : public Texture {
    public:
        virtual ~Texture3D() = default;

        virtual uint32_t GetDepth() const = 0;
    };

    class TextureManager {
    public:
    private:
        std::unordered_map<std::string, Ref<Texture>> mTextures;
    };

    class TextureLoader {
    public:
        static Ref<Texture2D> LoadTexture2DFromFile(const std::filesystem::path& path);
        static Ref<Texture2D> LoadTexture2DFromMemory(uint32_t width, uint32_t height, const u_char* data);
    };

    class Texture2D_OpenGL : public Texture2D {
    public:

        Texture2D_OpenGL(const std::filesystem::path& path);
        Texture2D_OpenGL(uint32_t width, uint32_t height, const u_char* data);
        virtual ~Texture2D_OpenGL() = default;

        [[nodiscard]] virtual uint32_t GetWidth() override { return mWidth; }
        [[nodiscard]] virtual uint32_t GetHeight() override { return mHeight; }
        [[nodiscard]] virtual uint32_t GetTextureID() override { return mTextureID; };
        [[nodiscard]] virtual uint32_t GetTextureHash() override { return mTextureHash; }

    private: 

        u_char* GetDataFromImage(const std::filesystem::path& path);
        void CreateTextureAndSetData(const u_char* textureData);

    private:
        uint32_t mTextureHash;
        uint32_t mTextureID;

        uint32_t mWidth;
        uint32_t mHeight;

        uint32_t mFormat;
        uint32_t mInternalFormat;
    };
} // namespace Engine
#endif // ENGINE_TEXTURE_SYSTEM_SKETCH_HPP