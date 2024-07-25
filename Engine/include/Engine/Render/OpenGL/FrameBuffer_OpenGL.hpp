#ifndef ENGINE_FRAMEBUFFER_OPENGL_HPP
#define ENGINE_FRAMEBUFFER_OPENGL_HPP

#include "Engine/Render/FrameBuffer.hpp"

namespace Engine {

    class OpenGLFrameBuffer : public FrameBuffer {
    public:
        OpenGLFrameBuffer(const FrameBufferData& initData);
        virtual ~OpenGLFrameBuffer();

        void Invalidate();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void SetSize(uint32_t width, uint32_t height) override;
        virtual uint32_t GetColorAttachment() const override { return m_ColorAttachment; }
        virtual const FrameBufferData &GetBufferData() const override { return m_Data; }
    private:
        FrameBufferData m_Data;
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0;
        uint32_t m_DepthAttachment = 0;
    };

}

#endif //ENGINE_FRAMEBUFFER_OPENGL_HPP
