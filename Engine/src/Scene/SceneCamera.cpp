#include "Engine/Scene/SceneCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "Engine/engine_precompile_headers.hpp"


namespace Engine {
    SceneCamera::SceneCamera() {
        CalculateProjection();
    }

    void SceneCamera::SetOrthographic(float size, float near, float far) {
        m_ProjectionType = ProjectionType::Orthographic;
        m_OrthSize = size;
        m_OrthFar = far;
        m_OrthNear = near;

        CalculateProjection();
    }

    void SceneCamera::SetPerspective(float viewAngle, float near, float far) {
        m_ProjectionType = ProjectionType::Perspective;
        m_PerspectiveViewAngle = viewAngle; 
        m_PerspectiveNear = near;
        m_PerspectiveFar = far;

        CalculateProjection();    
    }

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height) {
        m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
        CalculateProjection();
    }


    void SceneCamera::CalculateProjection() {
        if (m_ProjectionType == ProjectionType::Perspective) {
            m_Projection = glm::perspective(m_PerspectiveViewAngle, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
            return;
        }

        float orthLeft = -m_OrthSize * m_AspectRatio * 0.5f;
        float orthRight = m_OrthSize * m_AspectRatio * 0.5f;
        float orthBottom = -m_OrthSize * 0.5f;
        float orttTop  = m_OrthSize * 0.5f;

        m_Projection = glm::ortho(orthLeft, orthRight, orthBottom, orttTop, m_OrthNear, m_OrthFar);
    }
}
