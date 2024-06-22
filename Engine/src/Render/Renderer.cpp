#include "Engine/Render/Renderer.hpp"
#include "Engine/Render/RenderCommand.hpp"
#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }


    void Renderer::EndScene()
    {

    }


    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
    {
        shader->Bind();
        shader->SetUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Engine
