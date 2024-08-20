#ifndef ENGINE_RENDERABLECOMPONENTS_HPP
#define ENGINE_RENDERABLECOMPONENTS_HPP

#include <glm/glm.hpp>
#include "Engine/Render/Texture/Textures.hpp"
#include "Engine/Render/Texture/TextureLoader.hpp"


namespace Engine {
    struct SpriteComponent {
        glm::vec4 Color = glm::vec4(1.0f);
        Ref<Texture2D> Texture /*= TextureManager::CreateTexture(512, 512, glm::vec4(1.f))*/;
        float Scale = 1.f;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;

        explicit SpriteComponent(const glm::vec4& color) : Color(color) {};
    };
}

#endif //ENGINE_RENDERABLECOMPONENTS_HPP
