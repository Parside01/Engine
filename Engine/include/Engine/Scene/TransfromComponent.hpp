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

        explicit FPosition(const float x, const float y, const float z) : x(x), y(y), z(z) {}
        explicit FPosition(const float val = 1.0f) : x(val), y(val), z(val) {}
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

        explicit FRotation(const float v)
        : Roll(v), Pitch(v), Yaw(v), rx(v), ry(v), rz(v) {}
        explicit FRotation(const float roll, const float pitch, const float yaw)
            : Roll(roll), Pitch(pitch), Yaw(yaw), rx(roll), ry(pitch), rz(yaw) {}
    };

    struct FScale {
        float sx{1.0f};
        float sy{1.0f};
        float sz{1.0f};

        FScale(const FScale&) = default;

        explicit FScale(const float v)
            : sx(v), sy(v), sz(v) {}
        explicit  FScale(const float x, const float y, const float z)
            : sx(x), sy(y), sz(z) {}
    };

    struct TransformComponent {
        FPosition Position;
        FRotation Rotation;
        FScale Scale;

        explicit TransformComponent(const FPosition& position, const FRotation& rotation, const FScale& scale)
            : Position(position), Rotation(rotation), Scale(scale) {}
    };
}

#endif //ENGINE_TRANSFROM_HPP
