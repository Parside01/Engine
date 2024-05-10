#ifndef ENGINE_BUFFERS_HPP
#define ENGINE_BUFFERS_HPP

#include "Engine/engine_precompile_headers.hpp"

namespace Engine
{
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static VertexBuffer* Create(float* vertices, size_t size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static IndexBuffer* Create(uint32_t* indexes, size_t size);
    };
} // namespace Engine


#endif