#include "../include/Application.hpp"
#include <iostream>

namespace Engine
{
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }
    Application::~Application() {

    }
    void Application::Run() {
        while (m_IsStart) {
            m_Window->OnUpdate();
        }
    }

    Application* CreateApplication() {
        return nullptr;
    }
} // namespace Engine

