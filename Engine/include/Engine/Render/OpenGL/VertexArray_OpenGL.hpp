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

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
    
        
        [[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override { return m_VertexBuffers; };
        [[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; };

    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer> > m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
} // namespace Engine


#endif