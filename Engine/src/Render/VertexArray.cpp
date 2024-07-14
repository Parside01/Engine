#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/VertexArray.hpp"
#include "Engine/Render/Renderer.hpp"
#include "Engine/Render/OpenGL/VertexArray_OpenGL.hpp"

namespace Engine
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI()) 
        {
            case RendererAPI::API::None: 
            {
                EG_CORE_ASSERT(false, "RedererAPI::None is not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
            {
                return std::make_shared<OpenGLVertexArray>();
            }
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
    
} // namespace Engine

