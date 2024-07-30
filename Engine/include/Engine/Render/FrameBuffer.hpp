#ifndef ENGINE_FRAMEBUFFER_HPP
#define ENGINE_FRAMEBUFFER_HPP


#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Core.hpp"

namespace Engine {

    enum class FramebufferTextureFormat {
        None = 0,
        RGBA8,
        RED_INTEGER,

        DEPTH,
        DEPTH24STENCIL8,

        Depth = DEPTH24STENCIL8
    };

    struct FramebufferTextureSpec {
        FramebufferTextureSpec() = default;
        FramebufferTextureSpec(FramebufferTextureFormat format) : TextureFormat(format) {}

        FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
    };

    struct FramebufferAttachmentSpec {
        FramebufferAttachmentSpec() = default;
        FramebufferAttachmentSpec(std::initializer_list<FramebufferTextureSpec> attachments) : Attachments(attachments) {}
        std::vector<FramebufferTextureSpec> Attachments;
    };

    struct FramebufferSpec {
        uint32_t Width;
        uint32_t Height;
        FramebufferAttachmentSpec Attachments;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class FrameBuffer {
    public:
        virtual ~FrameBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetSize(uint32_t width, uint32_t height) = 0; 
        virtual uint32_t GetColorAttachment(uint32_t index = 0) const = 0;

        virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

        virtual int ReadFromPixel(int attachmentIndex, int x, int y) = 0;

        virtual const FramebufferSpec& GetBufferData() const = 0;
        static Ref<FrameBuffer> Create(const FramebufferSpec& initData);
    };

}

#endif