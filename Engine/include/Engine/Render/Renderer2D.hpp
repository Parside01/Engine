#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP
#include <Engine/Scene/EditorCamera.hpp>

#include "Engine/Render/OrthCamera.hpp"
#include "Engine/Render/Texture/Textures.hpp"
#include "Engine/Render/Camera.hpp"

#include "Engine/Scene/TransfromComponent.hpp"
#include "Engine/Scene/RenderableComponents.hpp"

namespace Engine {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const Camera& camera, const glm::mat4 &transform);
        static void BeginScene(const EditorCamera& camera);
        static void BeginScene(const OrthCamera& camera);
        static void Flush();
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::quat& rotation, const glm::vec4& color, int entityID);

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);
        static void DrawQuad(int entityID, const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale = 1.0f);

        static void DrawQuadEntity(int EntityID, const TransformComponent& transformComponent, const SpriteComponent& spriteComponent);

    private:
        static void FlushAndReset();
    };
}

#endif //RENDERER2D_HPP
