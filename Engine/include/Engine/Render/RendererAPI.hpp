#ifndef ENGINE_RENDERERAPI_HPP
#define ENGINE_RENDERERAPI_HPP

#include <glm/glm.hpp>
#include "Engine/Render/VertexArray.hpp"

namespace Engine
{
    class RendererAPI 
    {
    public:
        enum class API {
            None = 0, OpenGL = 1
        };

    public:

        virtual void Init() = 0;

        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
        virtual void DrawIndexedBaseVertex(const Ref<VertexArray> &vertexArray, uint32_t indexCount, uint32_t baseIndex, uint32_t baseVertex) = 0;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        [[nodiscard]] inline static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
} // namespace Engine



#endif