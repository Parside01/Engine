#ifndef ENGINE_SUBTEXTURE_HPP
#define ENGINE_SUBTEXTURE_HPP

#include "Engine/Render/Texture.hpp"
#include <glm/glm.hpp>

namespace Engine {
    class SubTexture2D {
    public:

        SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& minPos, const glm::vec2& maxPos);

        static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& textureSize);

        const Ref<Texture2D>& GetTexture() const { return m_Texture; }
        const glm::vec2* GetTextureCoords() const { return m_TextureCoords; }

    private:

        Ref<Texture2D> m_Texture; 
        glm::vec2 m_TextureCoords[4];
    };
}

#endif
