#include "Engine/Render/OpenGL/RendererAPI_OpenGL.hpp"
#include "Engine/engine_precompile_headers.hpp"
#include <GL/glew.h>

namespace Engine
{
    void OpenGLRendererAPI::Init() {
        glewExperimental = GL_TRUE;
        glewInit();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {
        uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::DrawIndexedBaseVertex(const Ref<VertexArray> &vertexArray, uint32_t indexCount, uint32_t baseIndex, uint32_t baseVertex) {
        uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
        glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, reinterpret_cast<void*>(sizeof(uint32_t) * baseIndex), baseVertex);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }
} // namespace Engine
