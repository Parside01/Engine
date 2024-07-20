#include "Engine/Render/SubTexture2D.hpp"
#include "Engine/engine_precompile_headers.hpp"

namespace Engine {
    SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& minPos, const glm::vec2& maxPos) 
    : m_Texture(texture) 
    {
        m_TextureCoords[0] = {minPos.x, minPos.y};
        m_TextureCoords[1] = {maxPos.x, minPos.y};
        m_TextureCoords[2] = {maxPos.x, maxPos.y};
        m_TextureCoords[3] = {minPos.x, maxPos.y};
    }

    Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& textureSize) {
        const glm::vec2 minPos = { (coords.x * textureSize.x) / texture->GetWidth(), (coords.y * textureSize.y) / texture->GetHeight() };
        const glm::vec2 maxPos = { ((coords.x + 1) * textureSize.x) / texture->GetWidth(), ((coords.y + 1) * textureSize.y) / texture->GetHeight() };
        return std::make_shared<SubTexture2D>(SubTexture2D(texture, minPos, maxPos));
    }
}