#include "Engine/Render/Buffers.hpp"
#include "Engine/Render/OpenGL/Buffers_OpenGL.hpp"
#include "Engine/Render/Renderer.hpp"
#include "Engine/log/Log.hpp"


namespace Engine
{
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: {
                EG_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL: {
                return std::make_shared<OpenGLVertexBuffer>(size);
            }
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, size_t size) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: {
                EG_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL: {
                return std::make_shared<OpenGLVertexBuffer>(vertices, size);
            }
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indexes, size_t count) {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: {
                EG_ASSERT(false, "RendererAPI::None is not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL: {
                return std::make_shared<OpenGLIndexBuffer>(indexes, count);
            }
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
} // namespace Engine
