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

        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        [[nodiscard]] inline static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
} // namespace Engine



#endif