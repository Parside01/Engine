#ifndef ENGINE_BUFFERS_OPENGL_HPP
#define ENGINE_BUFFERS_OPENGL_HPP

#include "Engine/Render/Buffers.hpp"

namespace Engine
{
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(float* vertices, size_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetData(const void* data, uint32_t size) override;

        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        [[nodiscard]] virtual const BufferLayout& GetLayout() const override { return m_Layout; }
    
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indexes, size_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        [[nodiscard]] uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_Count;
        uint32_t m_RendererID;
    };
} // namespace Engine


#endif