#ifndef ENGINE_UNIFORMBUFFER_OPENGL_HPP
#define ENGINE_UNIFORMBUFFER_OPENGL_HPP
#include <Engine/Render/UniformBuffer.hpp>

namespace Engine {
    class OpenGLUniformBuffer : public UniformBuffer {
    public:
        OpenGLUniformBuffer(uint32_t size, uint32_t binding);
        virtual ~OpenGLUniformBuffer();

        virtual void SetData(const void *data, uint32_t size, uint32_t offset) override;
    private:
        uint32_t mBufferID = 0;
    };
}

#endif //ENGINE_UNIFORMBUFFER_OPENGL_HPP
