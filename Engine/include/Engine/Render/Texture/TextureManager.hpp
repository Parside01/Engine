#ifndef ENGINE_TEXTUREMANAGER_HPP
#define ENGINE_TEXTUREMANAGER_HPP

#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/Texture/Textures.hpp"
#include "Engine/Render/Texture/TextureAtlas.hpp"


namespace Engine {

    class TextureManager {
    public:

        TextureManager() = default;

        static void Init();

        static Ref<Texture2D> CreateTexture(const std::string& path);
        static Ref<Texture2D> CreateTexture(uint32_t width, uint32_t height, const glm::vec4& color);

        static void ResizeTexture(uint32_t newWidth, uint32_t newHeight, Ref<Texture2D> &texture);

        static void BindTextures();

        static std::array<glm::vec2, 4> GetTextureCoords(const Ref<Texture2D>& texture);
        static uint32_t GetTextureSlot(const Ref<Texture2D>& texture);
        static Scope<TextureAtlas>& GetTextureAtlas() { return mTextureAtlas; }
        static uint32_t GetRendererID(const Ref<Texture2D>& texture) { return mTextureAtlas->GetRendererID(); }

    private:
        static uint32_t mTextureSlotIndex;
        static Scope<TextureAtlas> mTextureAtlas;
    };

}


#endif //ENGINE_TEXTUREMANAGER_HPP
