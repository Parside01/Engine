#include "../include/Application.hpp"
#include "Application.hpp"

namespace Engine
{
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(EG_BINDEVENT(Application::OnEvent));
    }

    void Application::OnEvent(Event &event) {
        EG_CORE_TRACE("{0}", event.ToString());

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(EG_BINDFUNC(Application::OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent();
            if (event.Handled)
                break;
        }
    }

    void Application::OnWindowClose(WindowCloseEvent &event) {
        m_IsStart = false;
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
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
} // namespace Engine

