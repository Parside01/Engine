// #include "../include/Application.hpp"
// #include "../include/Input.hpp"

#include "Engine/Application.hpp"
#include "Engine/input/Input.hpp"

namespace Engine
{
    Application* Application::m_Instance = nullptr; 

    Application::Application() {
        EG_ASSERT(!m_Instance, "Application is exist");
        m_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(EG_BINDEVENT(Application::OnEvent));
    }

    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(EG_BINDEVENT(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &event) {
        m_IsStart = false;
        return true;
    }

    void Application::PushLayer(Layer *layer)
    {      
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    Application::~Application()
    {
    }

    void Application::Run() {
        while (m_IsStart) {
            
            for (Layer* l : m_LayerStack) {
                l->OnUpdate();
            }
            
            m_Window->OnUpdate();
        }
    }

    Application* CreateApplication() {
        return nullptr;
    }
} // namespace Engine

