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

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

    };
} // namespace Engine


#endif