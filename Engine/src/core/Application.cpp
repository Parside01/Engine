#include "../include/Application.hpp"

namespace Engine
{
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(EG_BINDEVENT(Application::OnEvent));
    }
    void Application::OnEvent(Event &event) {
        EG_CORE_INFO("{0}", event.ToString());
    }
    Application::~Application() {

    }
    void Application::Run() {
        while (m_IsStart) {
            m_Window->OnUpdate();
        }
    }


    Application *CreateApplication()
    {
        return nullptr;
    }
} // namespace Engine

