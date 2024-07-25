#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP
#include "Engine/Render/OrthCamera.hpp"
#include "Engine/Render/Texture.hpp"
#include "Engine/Render/Camera.hpp"

namespace Engine {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera& camera, const glm::mat4 &transform);
        static void BeginScene(const OrthCamera& camera);
        static void Flush();
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);

    private:
        static void FlushAndReset();
    };
}

#endif //RENDERER2D_HPP
