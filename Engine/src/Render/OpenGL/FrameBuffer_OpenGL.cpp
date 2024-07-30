#include "Engine/Render/OpenGL/FrameBuffer_OpenGL.hpp"
#include <GL/glew.h>

#include "Engine/log/Log.hpp"

namespace Engine {

    static const uint32_t MaxSize{8192};

    static bool IsdepthFormat(FramebufferTextureFormat format) {
        switch (format) {
            case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
            default: return false;
        }
        return false;
    }

    static GLenum TextureTarget(bool multisample) {
        return multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
    }

    static void CreateTextures(bool multisample, uint32_t* outID, uint32_t count) {
        glCreateTextures(TextureTarget(multisample), count, outID);
    }

    static void BindTexture(bool multisample, uint32_t id) {
        glBindTexture(TextureTarget(multisample), id);
    }

    static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index) {
        bool multisample = samples > 1;
        if (multisample) glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisample), id, 0);
    }

    static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height) {
        bool multisample = samples > 1;
        if (multisample) glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
        else {
            glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisample), id, 0);
    }

    static GLenum ToOpenGLTextureFormat(FramebufferTextureFormat format) {
        switch (format) {
            case FramebufferTextureFormat::RGBA8: return GL_RGBA8;
            case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
        }
        EG_CORE_ASSERT(false);
        return 0;
    }


    OpenGLFrameBuffer::OpenGLFrameBuffer(const FramebufferSpec &initData) : m_Data(initData)
    {
        for (auto spec : m_Data.Attachments.Attachments) {
            if (!IsdepthFormat(spec.TextureFormat)) m_ColorAttachmentsSpecs.emplace_back(spec);
            else m_DepthAttachmentSpec = spec;
        }

        Invalidate();
    }
    void OpenGLFrameBuffer::ClearAttachment(uint32_t attachmentIndex, int value) {
        EG_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size()); 
        auto& spec = m_ColorAttachmentsSpecs[attachmentIndex];
        glClearTexImage(m_ColorAttachments[attachmentIndex], 0, ToOpenGLTextureFormat(spec.TextureFormat), GL_INT, &value);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer() {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void OpenGLFrameBuffer::Invalidate() {
        if (m_RendererID) {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
            glDeleteTextures(1, &m_DepthAttachment);

            m_ColorAttachments.clear();
            m_DepthAttachment = 0;
        }

        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        bool multisample = m_Data.Samples > 1;

        if (m_ColorAttachmentsSpecs.size()) {
            m_ColorAttachments.resize(m_ColorAttachmentsSpecs.size());
            CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());
            for (size_t i{0}; i < m_ColorAttachments.size(); ++i) {
                BindTexture(multisample, m_ColorAttachments[i]);
                switch (m_ColorAttachmentsSpecs[i].TextureFormat) {
                    case FramebufferTextureFormat::RGBA8:
                        AttachColorTexture(m_ColorAttachments[i], m_Data.Samples, GL_RGBA8, GL_RGBA, m_Data.Width, m_Data.Height, i);
                        break;
                    case FramebufferTextureFormat::RED_INTEGER:
                        AttachColorTexture(m_ColorAttachments[i], m_Data.Samples, GL_R32I, GL_RED_INTEGER, m_Data.Width, m_Data.Height, i);
                        break;
                    default: break;
                }
            }
        }

        if (m_DepthAttachmentSpec.TextureFormat != FramebufferTextureFormat::None) {
            CreateTextures(multisample, &m_DepthAttachment, 1);
            BindTexture(multisample, m_DepthAttachment);
            switch (m_DepthAttachmentSpec.TextureFormat) {
                case FramebufferTextureFormat::DEPTH24STENCIL8:
                    AttachDepthTexture(m_DepthAttachment, m_Data.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Data.Width, m_Data.Height);
                    break;
                default: ;
            }
        }

        if (m_ColorAttachments.size() > 1) {
            EG_CORE_ASSERT(m_ColorAttachments.size() <= 4);
            GLenum buffers[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
            glDrawBuffers(m_ColorAttachments.size(), buffers);
        } else if (m_ColorAttachments.empty()) {
            glDrawBuffer(GL_NONE);
        }

        EG_CORE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Не получилось создать FrameBuffer")

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::SetSize(uint32_t width, uint32_t height) {
        if (width == 0 || height == 0 || width > MaxSize || height > MaxSize) return;

        m_Data.Height = height;
        m_Data.Width = width;

        Invalidate();
    }

    void OpenGLFrameBuffer::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Data.Width, m_Data.Height);
        
    }

    void OpenGLFrameBuffer::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    int OpenGLFrameBuffer::ReadFromPixel(int attachmentIndex, int x, int y) {
        EG_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size() && attachmentIndex >= 0);
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        int pixelData;
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
        return pixelData;
    } 

}
