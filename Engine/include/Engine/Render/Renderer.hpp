#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include "Engine/Render/RendererAPI.hpp"

namespace Engine
{
    class Renderer {
    public:

        static void BeginScene(); 
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& VertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
} // namespace Engine


#endif