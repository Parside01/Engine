#include "Engine/Scene/Systems/TransformSystem.hpp"
#include "Engine/Scene/Scene.hpp"
#include "Engine/benchmark/Benchmark.hpp"

namespace Engine
{   
    glm::mat4 TransformSystem::CalculateTransform(const TransformComponent& transformComponent) {
        return glm::translate(glm::mat4(1.0f), transformComponent.Position) * glm::mat4_cast(transformComponent.Rotation) * glm::scale(glm::mat4(1.0f), transformComponent.Scale);
    }

    glm::quat TransformSystem::EulerToQuat(const glm::vec3& euler) {
        return glm::quat(glm::radians(euler));
    }

    glm::vec3 TransformSystem::QuatToEuler(const glm::quat& quat) {
        return glm::degrees(glm::eulerAngles(quat));
    }
} // namespace Engine
