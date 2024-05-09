#ifndef ENGINE_RENDERCONTEXT_OPENGL_HPP
#define ENGINE_RENDERCONTEXT_OPENGL_HPP

#include "Engine/Render/RenderContext.hpp"
#include "Engine/log/Log.hpp"


#include <GLFW/glfw3.h>
#include <GL/gl.h>

namespace Engine
{
    class OpenGLContext : public RenderContext {
    public:
        OpenGLContext(GLFWwindow* window);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    
    private:

        GLFWwindow* m_WindowHandle;

    };
} // namespace Engine



#endif