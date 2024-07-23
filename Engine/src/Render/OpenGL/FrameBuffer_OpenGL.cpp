#include "Engine/Render/OpenGL/FrameBuffer_OpenGL.hpp"
#include <GL/glew.h>

#include "Engine/log/Log.hpp"

namespace Engine {
    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferData &initData) : m_Data(initData)
    {
        Invalidate();
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer() {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(1, &m_ColorAttachment);
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void OpenGLFrameBuffer::Invalidate() {
        if (m_RendererID) {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Data.Width, m_Data.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Data.Width, m_Data.Height);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Data.Width, m_Data.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

        EG_CORE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Не получилось создать FrameBuffer")

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::SetSize(uint32_t width, uint32_t height) {
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
}
