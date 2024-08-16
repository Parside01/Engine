#include "Engine/Render/OpenGL/Buffers_OpenGL.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include <GL/glew.h>
#include <GL/gl.h> 

namespace Engine {

    //------------------------------------------------------------------//
    ///////////////////////// VertexBuffer ///////////////////////////////
    //------------------------------------------------------------------//
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
        EG_PROFILE_FUNC();

        GLCall(glCreateBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
        GLCall(glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW));
    }
    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, size_t size) {
        EG_PROFILE_FUNC();
        GLCall(glCreateBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
        GLCall(glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW));
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        EG_PROFILE_FUNC();
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void OpenGLVertexBuffer::Bind() const {
        EG_PROFILE_FUNC();
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    }

    void OpenGLVertexBuffer::Unbind() const {
        EG_PROFILE_FUNC();
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) {
        EG_PROFILE_FUNC();

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    }

    //------------------------------------------------------------------//
    ///////////////////////// VertexBuffer ///////////////////////////////
    //------------------------------------------------------------------//


    //------------------------------------------------------------------//
    ///////////////////////// IndexBuffer ////////////////////////////////
    //------------------------------------------------------------------//
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indexes, size_t count) 
    : m_Count(count) {
        EG_PROFILE_FUNC();
        GLCall(glCreateBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indexes, GL_STATIC_DRAW));

    }

    void OpenGLIndexBuffer::Bind() const {
        EG_PROFILE_FUNC();
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void OpenGLIndexBuffer::Unbind() const {
        EG_PROFILE_FUNC();
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        EG_PROFILE_FUNC();
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }
    //------------------------------------------------------------------//
    ///////////////////////// IndexBuffer ////////////////////////////////
    //------------------------------------------------------------------//
}