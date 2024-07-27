#ifndef ENGINE_TRANSFORM_SYSTEM_HPP
#define ENGINE_TRANSFORM_SYSTEM_HPP

#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>
#include "Engine/Scene/TransfromComponent.hpp"

namespace Engine
{
    class Scene;

    // Эта штука предназначена для расчета трансформаций объектов в сцене, может обновлять в их в каждом кадре.
    class TransformSystem {
    public: 
        TransformSystem() = default;
        virtual ~TransformSystem() = default;

        static glm::mat4 CalculateTransform(const TransformComponent& transformComponent);
        static glm::quat EulerToQuat(const glm::vec3& euler);
        static glm::vec3 QuatToEuler(const glm::quat& quat);
    };
} // namespace Engine


#endif // ENGINE_TRANSFORM_SYSTEM_HPP