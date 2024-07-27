#ifndef ENGINE_TRANSFROM_HPP
#define ENGINE_TRANSFROM_HPP

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine {
    struct FPosition {
        float x{0.0f};
        float y{0.0f};
        float z{0.0f};

        FPosition(const FPosition&) = default;

        FPosition(const float x, const float y, const float z) : x(x), y(y), z(z) {}
        FPosition(const float val = 1.0f) : x(val), y(val), z(val) {}
    };

    // Everything is in radians.
    struct FRotation {
        float Roll{0.0f};
        float Pitch{0.0f};
        float Yaw{0.0f};

        float rx{0.0f}; // Similary Roll.
        float ry{0.0f}; // Similary Pitch.
        float rz{0.0f}; // Similary Yaw.

        FRotation(const FRotation&) = default;

        FRotation(const float v)
        : Roll(v), Pitch(v), Yaw(v), rx(v), ry(v), rz(v) {}
        FRotation(const float roll, const float pitch, const float yaw)
            : Roll(roll), Pitch(pitch), Yaw(yaw), rx(roll), ry(pitch), rz(yaw) {}
    };

    struct FScale {
        float sx{1.0f};
        float sy{1.0f};
        float sz{1.0f};

        FScale(const FScale&) = default;

        FScale(const float v)
            : sx(v), sy(v), sz(v) {}
        FScale(const float x, const float y, const float z)
            : sx(x), sy(y), sz(z) {}
    };

    struct TransformComponent {
        glm::vec3 Position = glm::vec3(0.0f);
        glm::quat Rotation = glm::quat(glm::vec3(0.0f)); // TODO: Поработать над тем как работают кватернионы, возможно просто переключиться на обыный 3х мерыный вектор для ротации.
        glm::vec3 Scale = glm::vec3(1.0f);
        
        TransformComponent() = default;
        TransformComponent(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
            : Position(position), Rotation(rotation), Scale(scale) {}
    };


}

#endif //ENGINE_TRANSFROM_HPP
