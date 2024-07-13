#ifndef ORTHCAMERACONTROLLER_HPP
#define ORTHCAMERACONTROLLER_HPP

#include "Engine/Timestep.hpp"
#include "Engine/events/AppEvent.hpp"
#include "Engine/events/MouseEvent.hpp"
#include "Engine/Render/OrthCamera.hpp"
namespace Engine {

    class OrthCameraController {
    public:

        OrthCameraController(float aspectRatio, bool itRotate = false);

        void OnUpdate(Timestep tick);
        void OnEvent(Event& event);
    private:

        bool OnMouseScrolled(MouseScrolledEvent& event);
        bool OnWindowResize(WindowResizeEvent& event);

    private:
        bool m_ItRotate;

        float m_AspectRatio;
        float m_ZoomLevel{1.0f};

        float m_CameraRotation{0.f};
        float m_CameraRotationSpeed{1.f};
        float m_CameraTranslationSpeed{1.f};
        glm::vec3 m_CameraPosition{0.f, 0.f, 0.f};

        OrthCamera m_Camera;
    };
}

#endif //ORTHCAMERACONTROLLER_HPP
