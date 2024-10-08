#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <glm/glm.hpp>

namespace Engine {

    class Camera {
    public:
        Camera() = default;
        explicit Camera(const glm::mat4& projection) : m_Projection(projection) {}
        virtual ~Camera() {};

        const glm::mat4& GetProjection() const { return m_Projection; }

    protected:
        glm::mat4 m_Projection{glm::mat4(1.0f)};
    };

}

#endif //ENGINE_CAMERA_HPP
