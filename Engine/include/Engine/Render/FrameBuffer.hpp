#ifndef ENGINE_FRAMEBUFFER_HPP
#define ENGINE_FRAMEBUFFER_HPP

#include "Engine/Core.hpp"

namespace Engine {

    struct FrameBufferData {
        uint32_t Width;
        uint32_t Height;
    };

    class FrameBuffer {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void SetSize(uint32_t width, uint32_t height) = 0;
        virtual uint32_t GetColorAttachment() const = 0;

        virtual const FrameBufferData& GetBufferData() const = 0;
        static Ref<FrameBuffer> Create(const FrameBufferData& initData);
    };

}

#endif