#include "../include/window/linux_window.hpp"
#include "../include/log/Log.hpp"

namespace Engine {
    
    static bool s_GLFWInit = false;

    Window* Window::Create(const WindowProrepty& props) {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProrepty& props) {
        Init(props);
    }

    LinuxWindow::~LinuxWindow() {
        Shitdown();
    }

    void LinuxWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void LinuxWindow::SetVsync(bool enabled) {
        
        if (enabled) 
            glfwSwapInterval(1);
        else 
            glfwSwapInterval(0);
        m_WindowData.Vsync = enabled;
    }

    void LinuxWindow::Init(const WindowProrepty &props) {
        m_WindowData.Title = props.Title;
        m_WindowData.Width = props.Width;
        m_WindowData.Height = props.Height;

        EG_CORE_INFO("Create window --- {0} ({1} : {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInit) {
            int succ = glfwInit();
            
            EG_CORE_ASSERT(succ, "Failed init GLFW!");

            s_GLFWInit = true;
        }

        m_Window = glfwCreateWindow(int(m_WindowData.Width), int(m_WindowData.Height), m_WindowData.Title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
    }

    void LinuxWindow::Shitdown() {
        glfwDestroyWindow(m_Window);
    }
}