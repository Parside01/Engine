#include "Engine/Render/OpenGL/RenderContext_OpenGL.hpp"

namespace Engine
{
    OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowHandle(window) {
        
        EG_CORE_ASSERT(m_WindowHandle, "Window handle is null!");

    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);

    }

    void OpenGLContext::SwapBuffers() {
            glBegin(GL_TRIANGLES);

            glEnd();

        glfwSwapBuffers(m_WindowHandle);
    }
} // namespace Engine
