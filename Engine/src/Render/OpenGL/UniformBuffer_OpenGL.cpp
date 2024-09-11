#include <Engine/Render/OpenGL/UniformBuffer_OpenGL.hpp>
#include <GL/glew.h>

#ifdef ENGINE_API_OPENGL
namespace Engine {
    OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding) {
        glCreateBuffers(1, &mBufferID);
        glNamedBufferData(mBufferID, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, mBufferID);
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer() {
        glDeleteBuffers(1, &mBufferID);
    }

    void OpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset) {
        glNamedBufferSubData(mBufferID, offset, size, data);
    }
}

#endif