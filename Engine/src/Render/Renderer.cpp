#include "Engine/Render/OpenGL/Shader_OpenGL.hpp"
#include "Engine/Render/Renderer.hpp"
#include "Engine/Render/RenderCommand.hpp"
#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::Init() {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(OrthCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }


    void Renderer::EndScene()
    {

    }


    void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
    {
        shader->Bind();
        
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

} // namespace Engine
