#ifndef ENGINE_TRANSFROM_HPP
#define ENGINE_TRANSFROM_HPP

#include <glm/glm.hpp>

namespace Engine {
    struct Position {
        float x;
        float y;
        float z;
    };

    struct Rotation {
        float Roll;
        float Pitch;
        float Yaw;

        float rx; // Similary Roll.
        float ry; // Similary Pitch.
        float rz; // Similary Yaw.
    };

    struct Scale {
        float sx;
        float sy;
        float sz;
    };

    struct TransformComponent {
        glm::mat4 Transform;

        TransformComponent() = default;
        TransformComponent(const TransformComponent& transformComponent) = default;

        explicit TransformComponent(const glm::mat4& transformMatrix) : Transform(transformMatrix) {}
    };
}

#endif //ENGINE_TRANSFROM_HPP
