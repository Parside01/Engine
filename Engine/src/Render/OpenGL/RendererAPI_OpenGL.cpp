#include "Engine/Render/OpenGL/RendererAPI_OpenGL.hpp"
#include "Engine/engine_precompile_headers.hpp"
#include <GL/glew.h>

namespace Engine
{
    void OpenGLRendererAPI::Clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
} // namespace Engine
