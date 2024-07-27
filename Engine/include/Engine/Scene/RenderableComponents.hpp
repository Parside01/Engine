#ifndef ENGINE_RENDERABLECOMPONENTS_HPP
#define ENGINE_RENDERABLECOMPONENTS_HPP

#include <glm/glm.hpp>

namespace Engine {
    struct SpriteComponent {
        glm::vec4 Color;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;

        explicit SpriteComponent(const glm::vec4& color = glm::vec4(1.0f)) : Color(color) {};
    };
}

#endif //ENGINE_RENDERABLECOMPONENTS_HPP
