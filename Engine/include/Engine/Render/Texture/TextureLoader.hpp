#ifndef ENGINE_TEXTURELOADER_HPP
#define ENGINE_TEXTURELOADER_HPP

#include "Engine/Render/Texture/Textures.hpp"
#include "Engine/Render/Texture/TextureManager.hpp"

namespace Engine {

    class TextureLoader {
    public:
        // static Ref<Texture2D> LoadTexture2DFromColor(uint32_t width, uint32_t height, const glm::vec4& color);
        static Ref<Texture2D> LoadTexture2DFromFile(const std::filesystem::path& path);
        // static Ref<Texture2D> LoadTexture2DFromMemory(uint32_t width, uint32_t height, const u_char* data);
        static TextureManager& GetTextureManager() { return sTextureManager; }
    private:
        static TextureManager sTextureManager;
    };
}

#endif // ENGINE_TEXTURELOADER_HPP
