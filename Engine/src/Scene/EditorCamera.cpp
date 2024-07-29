#include "Engine/Scene/EditorCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/input/Input.hpp"
#include "Engine/input/MouseCodes.hpp"
#include "Engine/input/KeyCodes.hpp"
#include "Engine/log/Log.hpp"

namespace Engine
{
    EditorCamera::EditorCamera(float fov, float aspectRatio, float near, float far)
        : m_FOV(fov), m_AspectRatio(aspectRatio), m_Near(near), m_Far(far), Camera(glm::perspective(glm::radians(fov), aspectRatio, near, far))
    {
        CalculateView();
    }

    void EditorCamera::OnUpdate(float tick) {
        if (Input::IsKeyPressed(EG_KEY_LEFT_ALT)) {
            const glm::vec2& mouse = { Input::GetMouseX(), Input::GetMouseY() };
            glm::vec2 delta = (mouse - m_MousePosition) * 0.003f;
            m_MousePosition = mouse;

            if (Input::IsKeyPressed(EG_KEY_A)) 
                MousePan(delta);
            else if (Input::IsKeyPressed(EG_KEY_D))
                MouseRotate(delta);
            else if (Input::IsKeyPressed(EG_KEY_W)) 
                MouseZoom(delta.y);
        }
        CalculateView();
    }

    void EditorCamera::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseScrolledEvent>(EG_BINDEVENT(EditorCamera::OnMouseScroll));
    }

    glm::vec3 EditorCamera::CalculatePosition() {
        return m_FocalPoint - GetForwardDirection() * m_Distance;
    }

    glm::vec3 EditorCamera::GetUpDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.f, 1.f, 0.f));
    }

    glm::vec3 EditorCamera::GetRightDiraction() const {
        return glm::rotate(GetOrientation(), glm::vec3(1.f, 0.f, 0.f));
    }

    glm::vec3 EditorCamera::GetForwardDirection() const {
        return glm::rotate(GetOrientation(), glm::vec3(0.f, 0.f, -1.f));
    }

    glm::quat EditorCamera::GetOrientation() const {
        return glm::quat(m_Rotation * -1.f);
    }

    std::pair<float, float> EditorCamera::PanSpeed() const {
        float x = std::min(m_ViewportWidth / 1000.f, 2.4f);
        float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

        float y = std::min(m_ViewportHeight / 1000.f, 2.4f);
        float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;
        return {xFactor, yFactor};
    }
    float EditorCamera::ZoomSpeed() const {
        float distance = m_Distance * 0.2f;
        distance = std::max(distance, 0.0f);
        float speed = std::min(distance * distance, 100.f);
        return speed;
    }

    bool EditorCamera::OnMouseScroll(MouseScrolledEvent &event) {
        float delta = event.GetYOffset() * 0.1f;
        MouseZoom(delta);
        CalculateView();
        return false;
    }


    float EditorCamera::GetRotationSpeed() const {
        return m_RotationSpeed;
    }

    void EditorCamera::MousePan(const glm::vec2 &delta) {
        auto [xSpeed, ySpeed] = PanSpeed();
        m_FocalPoint += -GetRightDiraction() * delta.x * xSpeed * m_Distance;
        m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;
    }

    void EditorCamera::MouseRotate(const glm::vec2 &delta) {
        float yawSign = GetUpDirection().y < 0 ? -1.f : 1.f;
        m_Rotation.y  += yawSign * delta.x * GetRotationSpeed();
        m_Rotation.x += delta.y * GetRotationSpeed();
    }

    void EditorCamera::MouseZoom(float delta) {
        m_Distance -= delta * ZoomSpeed();
        if (m_Distance >= 1.f) return;
        m_FocalPoint += GetForwardDirection();
        m_Distance = 1.f;
    }

    void EditorCamera::CalculateProjection() {
        m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
        m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
    }

    void EditorCamera::CalculateView() {
        m_Position = CalculatePosition();

        glm::quat origentation = GetOrientation();
        m_ViewMatrix = glm::translate(glm::mat4(1.f), m_Position) * glm::toMat4(origentation);
        m_ViewMatrix = glm::inverse(m_ViewMatrix);
    }
} // namespace Engine
