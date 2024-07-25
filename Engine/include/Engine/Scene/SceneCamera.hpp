#ifndef ENGINE_SCENECAMERA_HPP
#define ENGINE_SCENECAMERA_HPP

#include "Engine/Render/Camera.hpp"

namespace Engine {

    class SceneCamera : public Camera {
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        void SetOrthographic(float size, float near, float far);
        void SetViewportSize(uint32_t width, uint32_t height);
    private:
        void CalculateProjection();
    private:
        float m_OrthSize = 10.0f;
        float m_OrthNear = -1.0f;
        float m_OrthFar = 1.0f;

        float m_AspectRatio = 0.0f;
    };

}

#endif //ENGINE_SCENECAMERA_HPP
