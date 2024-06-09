#include "Engine/Render/OpenGL/RenderContext_OpenGL.hpp"

namespace Engine
{
    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowHandle(window) {
        
        EG_CORE_ASSERT(m_WindowHandle, "Window handle is null!");

    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);

        EG_CORE_INFO("OpenGLContext::Init -> OpenGL VERSION --- {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
        EG_CORE_INFO("OpenGLContext::Init -> OpenGL VENDOR --- {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        EG_CORE_INFO("OpenGLContext::Init -> OpenGL RENDERER --- {0}", reinterpret_cast<const char*>(glGetString(GL_RENDER)));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
} // namespace Engine
