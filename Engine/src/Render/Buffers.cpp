#include "Engine/Render/Buffers.hpp"
#include "Engine/Render/OpenGL/Buffers_OpenGL.hpp"
#include "Engine/Render/Renderer.hpp"
#include "Engine/log/Log.hpp"


namespace Engine
{
    VertexBuffer* VertexBuffer::Create(float* vertices, size_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: {
                EG_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL: {
                return new OpenGLVertexBuffer(vertices, size);
            }
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indexes, size_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: {
                EG_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL: {
                return new OpenGLIndexBuffer(indexes, size);
            }
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Engine
