#ifndef ENGINE_RENDERAPI_OPENGL_HPP
#define ENGINE_RENDERAPI_OPENGL_HPP

#include "Engine/Render/RendererAPI.hpp"

namespace Engine
{
    class OpenGLRendererAPI : public RendererAPI 
    {
    public:

        virtual void Init() override;

        virtual void Clear() override;
        virtual void SetClearColor(const glm::vec4& color) override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
        virtual void DrawIndexedBaseVertex(const Ref<VertexArray> &vertexArray, uint32_t indexCount, uint32_t baseIndex, uint32_t baseVertex) override;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    };
} // namespace Engine


#endif