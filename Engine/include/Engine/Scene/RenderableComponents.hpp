#ifndef ENGINE_RENDERABLECOMPONENTS_HPP
#define ENGINE_RENDERABLECOMPONENTS_HPP

#include <glm/glm.hpp>
#include "Engine/Render/Texture.hpp"

namespace Engine {
    struct SpriteComponent {
        glm::vec4 Color = glm::vec4(1.0f);
        Ref<Texture> Texture = Texture2D::Create(1, 1);
        float Scale = 1.f;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;

        explicit SpriteComponent(const glm::vec4& color) : Color(color) {};
    };
}

#endif //ENGINE_RENDERABLECOMPONENTS_HPP
