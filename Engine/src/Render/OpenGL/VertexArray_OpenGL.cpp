#include "Engine/Render/OpenGL/VertexArray_OpenGL.hpp"
#include <GL/glew.h>

namespace Engine
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Bool:   return GL_BOOL;
            default: return 0;
        }
        EG_CORE_ASSERT(false, "ShaderDataTypeToOpenGLBaseType - Unknow ShaderDataType");
        return 0;
    }
    #define TOSTRING(type) #type

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) 
    {
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        EG_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        const BufferLayout& layout = vertexBuffer->GetLayout();
        for (const auto& i : layout)
        {   
            switch (i.Type)
            {
                case ShaderDataType::Float: 
                case ShaderDataType::Float2: 
                case ShaderDataType::Float3: 
                case ShaderDataType::Float4: {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(
                        m_VertexBufferIndex,
                        i.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(i.Type),
                        i.Normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        reinterpret_cast<const void*>(i.Offset)
                    );
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Int: 
                case ShaderDataType::Int2: 
                case ShaderDataType::Int3: 
                case ShaderDataType::Int4: 
                case ShaderDataType::Bool: {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribIPointer(
                        m_VertexBufferIndex,
                        i.GetComponentCount(),
                        ShaderDataTypeToOpenGLBaseType(i.Type),
                        layout.GetStride(),
                        reinterpret_cast<const void*>(i.Offset)
                    );
                    m_VertexBufferIndex++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4: {
                    uint8_t count = i.GetComponentCount();
                    for (uint8_t j{0}; j < count; ++j) {
                        glEnableVertexAttribArray(m_VertexBufferIndex);
                        glVertexAttribPointer(
                            m_VertexBufferIndex,
                            count,
                            ShaderDataTypeToOpenGLBaseType(i.Type),
                            i.Normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(),
                            reinterpret_cast<const void*>(i.Offset + sizeof(float) * count * j)
                        );
                        glVertexAttribDivisor(m_VertexBufferIndex, 1);
                        m_VertexBufferIndex++;
                    }
                    break;
                }   
                std::cout << i.Name << std::endl; 
                EG_CORE_ASSERT(false, "OpenGLVertexArray::AddVertexBuffer - Unknow ShaderDataType");
                return;
            }
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

} // namespace Engine
