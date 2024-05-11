#include "Engine/Render/OpenGL/Buffers_OpenGL.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include <GL/glew.h>
#include <GL/gl.h> 

namespace Engine {

    //------------------------------------------------------------------//
    ///////////////////////// VertexBuffer ///////////////////////////////
    //------------------------------------------------------------------//
    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, size_t size) {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //------------------------------------------------------------------//
    ///////////////////////// VertexBuffer ///////////////////////////////
    //------------------------------------------------------------------//


    //------------------------------------------------------------------//
    ///////////////////////// IndexBuffer ////////////////////////////////
    //------------------------------------------------------------------//
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indexes, size_t count) 
    : m_Count(count) {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indexes, GL_STATIC_DRAW);

    }

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }
    //------------------------------------------------------------------//
    ///////////////////////// IndexBuffer ////////////////////////////////
    //------------------------------------------------------------------//
}