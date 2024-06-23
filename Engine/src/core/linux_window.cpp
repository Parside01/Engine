// #include "../include/window/linux_window.hpp"
// #include "../include/log/Log.hpp"

#include "Engine/window/linux_window.hpp"
#include "Engine/log/Log.hpp"

namespace Engine {
    
    static bool s_GLFWInit = false;

    static void GLFWErrorCallback(int error, const char* description) {
        EG_CORE_ERROR("GLFW Error [{0}]: {1}", error , description);
    }

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
        m_Context->SwapBuffers();
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
        m_Context = new OpenGLContext(m_Window);

        m_Context->Init();
        glfwSetWindowUserPointer(m_Window, &m_WindowData);

        // Set event callbacks.
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.Height = height;
            data.Width = width;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);

        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int code) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(code);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });

        glfwSetErrorCallback(GLFWErrorCallback);
    }

    void LinuxWindow::Shitdown() {
        glfwDestroyWindow(m_Window);
    }
}