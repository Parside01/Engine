#ifndef ENGINE_FRAMEBUFFER_OPENGL_HPP
#define ENGINE_FRAMEBUFFER_OPENGL_HPP
#include "Engine/log/Log.hpp"
#include "Engine/Render/FrameBuffer.hpp"

namespace Engine {

    class OpenGLFrameBuffer : public FrameBuffer {
    public:
        OpenGLFrameBuffer(const FramebufferSpec& initData);
        virtual ~OpenGLFrameBuffer();

        void Invalidate();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void SetSize(uint32_t width, uint32_t height) override;
        virtual uint32_t GetColorAttachment(uint32_t index = 0) const override { EG_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }
        virtual const FramebufferSpec &GetBufferData() const override { return m_Data; }

        virtual int ReadFromPixel(int attachmentIndex, int x, int y) override; 

        virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

    private:
        FramebufferSpec m_Data;
        uint32_t m_RendererID = 0;

        std::vector<FramebufferTextureSpec> m_ColorAttachmentsSpecs;
        FramebufferTextureSpec m_DepthAttachmentSpec;

        std::vector<uint32_t> m_ColorAttachments;
        uint32_t m_DepthAttachment = 0;
    };

}

#endif //ENGINE_FRAMEBUFFER_OPENGL_HPP
