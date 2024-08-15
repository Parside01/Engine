#ifndef ENGINE_TEXTUREATLAS_HPP
#define ENGINE_TEXTUREATLAS_HPP

#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/Texture/Textures.hpp"
#include "Engine/Render/Texture/TextureTypes.hpp"

namespace Engine {
    // Пока что поддерживает только 4 канала.
    class TextureAtlas {
        friend class TextureManager;
    public:
        TextureAtlas(TextureTarget target, uint32_t width, uint32_t height, uint32_t channels);
        TextureAtlas(const TextureSpec& spec);

        virtual ~TextureAtlas() = default;

        void AddTexture2D(const Ref<Texture2D>& texture);
        bool WriteAtlasInFile(const std::string& path) const;

        const glm::vec4& GetTextureCoords(uint32_t textureHash) const { return mTextureCoords.at(textureHash); }

        virtual void Bind(uint32_t slot = 0) = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual void Init() = 0;
    private:

        virtual void UpdateAtals() = 0;

    protected:
        Scope<u_char[]> mData;

        Scope<TextureSpec> mSpecefication;

        std::unordered_map<uint32_t, glm::vec4>  mTextureCoords;
        uint32_t mTextureSlot;

        uint32_t mxOffset = 0;
        uint32_t myOffset = 0;
    };

}

#endif //ENGINE_TEXTUREATLAS_HPP
