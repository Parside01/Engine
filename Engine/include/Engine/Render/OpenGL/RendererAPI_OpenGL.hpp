#ifndef ENGINE_RENDERAPI_OPENGL_HPP
#define ENGINE_RENDERAPI_OPENGL_HPP

#include "Engine/Render/RendererAPI.hpp"

namespace Engine
{
    class OpenGLRendererAPI : public RendererAPI 
    {
    public:

        virtual void Clear() override;
        virtual void SetClearColor(const glm::vec4& color) override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

    };
} // namespace Engine


#endif