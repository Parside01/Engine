#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/OrthCameraController.hpp"

namespace Engine {
    OrthCameraController::OrthCameraController(float aspectRatio, bool itRotate)
        : m_ItRotate(itRotate), m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {
    }

    void OrthCameraController::OnUpdate(Timestep tick) {

    }

    void OrthCameraController::OnEvent(Event &event) {
        EventDispatcher d(event);
        d.Dispatch<MouseScrolledEvent>(EG_BINDEVENT(OrthCameraController::OnMouseScrolled));
        d.Dispatch<WindowResizeEvent>(EG_BINDEVENT(OrthCameraController::OnWindowResize));
    }

    bool OrthCameraController::OnMouseScrolled(MouseScrolledEvent &event) {
        m_ZoomLevel -= event.GetYOffset();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthCameraController::OnWindowResize(WindowResizeEvent &event) {
        m_AspectRatio -= static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}
