#ifndef ENGINE_BUFFERS_HPP
#define ENGINE_BUFFERS_HPP

#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/Renderer.hpp"

namespace Engine
{
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static VertexBuffer* Create(float* vertices, size_t count);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indexes, size_t count);
    };
} // namespace Engine


#endif