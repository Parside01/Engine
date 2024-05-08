// #include "../include/window/linux_input.hpp"
// #include "../include/log/Log.hpp"

#include "Engine/input/linux_input.hpp"
#include "Engine/log/Log.hpp"

#include "GLFW/glfw3.h"

namespace Engine
{
    Input* Input::s_Instanse = new WindowsInput();
    
    bool WindowsInput::IsKeyPressed_Impl(int keycode) {
        
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());

        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressed_Impl(int button) {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());

        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    std::pair<float, float> WindowsInput::GetMousePosition_Impl() {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return { (float)x, (float)y };
    }

    float WindowsInput::GetMouseX_Impl() {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return (float)x;
    }

    float WindowsInput::GetMouseY_Impl() {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return (float)y;
    }

} // namespace Engine
