#ifndef ENGINE_SCENECAMERA_HPP
#define ENGINE_SCENECAMERA_HPP

#include "Engine/Render/Camera.hpp"

namespace Engine {

    class SceneCamera : public Camera {
    public:

        enum class ProjectionType {
            Perspective = 0,
            Orthographic = 1,
        };
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        void SetOrthographic(float size, float near, float far);
        void SetPerspective(float viewAngle, float near, float far);
        void SetViewportSize(uint32_t width, uint32_t height);

        float GetOrthographicSize() const { return m_OrthSize; }
        void SetOrthographicSize(float size) { m_OrthSize = size; CalculateProjection(); }

        float GetOrthographicNear() const { return m_OrthNear; }
        void SetOrthographicNear(float near) { m_OrthNear = near; CalculateProjection(); }

        float GetOrthographicFar() const { return m_OrthFar; }
        void SetOrthographicFar(float far) { m_OrthFar = far; CalculateProjection(); }

        float GetPerspectiveViewAngle() const { return m_PerspectiveViewAngle; }

        void SetPerspectiveViewAngle(float radians) { m_PerspectiveViewAngle = radians; CalculateProjection(); }
        float GetPerspectiveNear() const { return m_PerspectiveNear; }
        void SetPerspectiveNear(float near) { m_PerspectiveNear = near; CalculateProjection(); }

        float GetPerspectiveFar() const { return m_PerspectiveFar; }
        void SetPerspectiveFar(float far) { m_PerspectiveFar = far; CalculateProjection(); }

        ProjectionType GetProjectionType() const { return m_ProjectionType; }
        void SetProjectionType(ProjectionType type) { m_ProjectionType = type; }
    private:
        void CalculateProjection();
    private:

        ProjectionType m_ProjectionType = ProjectionType::Orthographic;

        float m_PerspectiveViewAngle = glm::radians(45.f);
        float m_PerspectiveNear = 0.01f; 
        float m_PerspectiveFar = 1000.0f;

        float m_OrthSize = 10.0f;
        float m_OrthNear = -1.0f;
        float m_OrthFar = 1.0f;

        float m_AspectRatio = 1.0f;
    };

}

#endif //ENGINE_SCENECAMERA_HPP
