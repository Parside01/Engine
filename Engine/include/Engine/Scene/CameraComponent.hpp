#ifndef ENGINE_CAMERACOMPONENT_HPP
#define ENGINE_CAMERACOMPONENT_HPP

#include "Engine/Scene/SceneCamera.hpp"

namespace Engine {

    struct CameraComponent {
        SceneCamera Camera;
        bool FixedAspectRatio = false;
        bool IsPrimary = true;

        CameraComponent() = default;
        CameraComponent(const CameraComponent& cameraComponent) = default;
    };

}

#endif //ENGINE_CAMERACOMPONENT_HPP
