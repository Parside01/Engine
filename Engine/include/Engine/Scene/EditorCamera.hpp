#ifndef ENGINE_EDITOR_CAMERA_HPP
#define ENGINE_EDITOR_CAMERA_HPP

#include <Engine/events/MouseEvent.hpp>

#include "Engine/Render/Camera.hpp"
#include "Engine/events/Event.hpp"
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
    // TODO: Сделать возможность регулировать все это через ui.
    class EditorCamera : public Camera {
    public: 

        EditorCamera();
        EditorCamera(float fov, float aspectRatio, float near, float far);

        void OnUpdate(float tick);
        void OnEvent(Event& event); 

        [[nodiscard]] inline float GetDistance() { return m_Distance; }
        inline void SetDistance(float distance) { m_Distance = distance; }

        inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; CalculateProjection(); }

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; } 
        const glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

        [[nodiscard]] glm::vec3 GetUpDirection() const; 
        [[nodiscard]] glm::vec3 GetRightDiraction() const;
        [[nodiscard]] glm::vec3 GetForwardDirection() const;
        [[nodiscard]] glm::vec3 GetPosition() const { return m_Position; }
        [[nodiscard]] glm::quat GetOrientation() const;

        [[nodiscard]] float GetRotationSpeed() const;
        void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }
    private:

        void CalculateProjection();
        void CalculateView();
        glm::vec3 CalculatePosition();

        std::pair<float, float> PanSpeed() const;
        void MousePan(const glm::vec2& delta);
        void MouseZoom(float delta);
        void MouseRotate(const glm::vec2& delta);

        float ZoomSpeed() const;

    private:

        bool OnMouseScroll(MouseScrolledEvent& event);

    private:
        float m_ViewportWidth = 1280;
        float m_ViewportHeight = 720;
        float m_Distance = 10.0f;

        float m_FOV = 45.f;
        float m_AspectRatio = 1.f;
        float m_Near = 0.f;
        float m_Far = 10.f;

        float m_RotationSpeed = 0.8f;

        glm::mat4 m_ViewMatrix = glm::mat4(1.f);

        glm::vec3 m_FocalPoint = glm::vec3(0.f);
        glm::vec3 m_Position = {0.f, 0.f, 0.f};
        glm::vec3 m_Rotation = glm::vec3(0.f);

        glm::vec2 m_MousePosition = glm::vec2(0.f);

    };

} // namespace Engine


#endif // ENGINE_EDITOR_CAMERA_HPP