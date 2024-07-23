#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/OrthCameraController.hpp"
#include "Engine/input/Input.hpp"
#include "Engine/input/KeyCodes.hpp"

namespace Engine {
    OrthCameraController::OrthCameraController(float aspectRatio, bool itRotate)
        : m_ItRotate(itRotate), m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {
    }

    void OrthCameraController::OnUpdate(Timestep tick) {
        if (Engine::Input::IsKeyPressed(EG_KEY_RIGHT))
            m_CameraPosition.x += m_CameraTranslationSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_LEFT))
            m_CameraPosition.x -= m_CameraTranslationSpeed * tick;

        if (Engine::Input::IsKeyPressed(EG_KEY_UP))
            m_CameraPosition.y += m_CameraTranslationSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_DOWN))
            m_CameraPosition.y -= m_CameraTranslationSpeed * tick;

        if (m_ItRotate) {
            m_Camera.SetRotation(m_CameraRotation);
        }
        m_Camera.SetPosition(m_CameraPosition);
        
        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthCameraController::OnEvent(Event &event) {
        EventDispatcher d(event);
        d.Dispatch<MouseScrolledEvent>(EG_BINDEVENT(OrthCameraController::OnMouseScrolled));
        d.Dispatch<WindowResizeEvent>(EG_BINDEVENT(OrthCameraController::OnWindowResize));
    }

    void OrthCameraController::OnResize(float width, float height) {
        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool OrthCameraController::OnMouseScrolled(MouseScrolledEvent &event) {
        m_ZoomLevel -= event.GetYOffset();
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthCameraController::OnWindowResize(WindowResizeEvent &event) {
        OnResize(static_cast<float>(event.GetWidth()), static_cast<float>(event.GetHeight()));
        return false;
    }
}
