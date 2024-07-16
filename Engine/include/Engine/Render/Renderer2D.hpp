#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP
#include "Engine/Render/OrthCamera.hpp"

namespace Engine {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthCamera& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);

    };
}

#endif //RENDERER2D_HPP
