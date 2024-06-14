#include "Engine/Render/Renderer.hpp"
#include "Engine/Render/RenderCommand.hpp"
#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    void Renderer::BeginScene() 
    {

    }


    void Renderer::EndScene()
    {

    }


    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) 
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Engine
