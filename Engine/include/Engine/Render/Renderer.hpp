#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include "Engine/Render/OrthCamera.hpp"
#include "Engine/Render/RendererAPI.hpp"
#include "Engine/Render/Shader.hpp"

namespace Engine
{
    class Renderer {
    public:

        static void BeginScene(OrthCamera& camera);
        static void EndScene();

        static void Submit(const Ref<VertexArray>& VertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
} // namespace Engine


#endif