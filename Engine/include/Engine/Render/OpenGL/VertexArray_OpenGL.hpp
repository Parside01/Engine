#ifndef ENGINE_VERTEXARRAY_OPENGL_HPP
#define ENGINE_VERTEXARRAY_OPENGL_HPP

#include "Engine/Render/VertexArray.hpp"

namespace Engine
{
    class OpenGLVertexArray : public VertexArray{
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() = default;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
    
        
        [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const override { return m_VertexBuffers; };
        [[nodiscard]] virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };

    private:
        uint32_t m_RendererID;
        std::vector<Ref<VertexBuffer> > m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
} // namespace Engine


#endif