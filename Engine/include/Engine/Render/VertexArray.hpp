#ifndef ENGINE_VERTEXARRAY_HPP
#define ENGINE_VERTEXARRAY_HPP


#include "Engine/Render/Buffers.hpp"

namespace Engine
{
    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        static VertexArray* Create();
    };
} // namespace Engine



#endif