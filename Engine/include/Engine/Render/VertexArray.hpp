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

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const = 0;
        [[nodiscard]] virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static VertexArray* Create();
    };
} // namespace Engine



#endif