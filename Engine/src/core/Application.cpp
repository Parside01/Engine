#include "Engine/Application.hpp"
#include "Engine/input/Input.hpp"
#include "Engine/Render/RenderCommand.hpp"
#include "Engine/Render/Renderer.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

#include <GLFW/glfw3.h>

namespace Engine
{
    Application* Application::m_Instance = nullptr; 

    Application::Application() {
        EG_ASSERT(!m_Instance, "Application is exist");

        m_Instance = this;
        
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(EG_BINDEVENT(Application::OnEvent));
        m_Window->SetVsync(true);
        Renderer::Init();

        m_GuiLayer = new GuiLayer();
        PushOverlay(m_GuiLayer);
    }

    void Application::OnEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(EG_BINDEVENT(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(EG_BINDEVENT(Application::OnWindowResize));
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

    bool Application::OnWindowResize(WindowResizeEvent &event) {
        if (event.GetHeight() == 0 || event.GetWidth() == 0) {
            m_Collapsed = true;
            return false;
        }
        m_Collapsed = false;

        m_Window->SetHeight(event.GetHeight());
        m_Window->SetWidth(event.GetWidth());
        Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

        return false;
    }


    void Application::PushLayer(Layer *layer) {      
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    Application::~Application() {
        delete m_GuiLayer;
    }

    void Application::Run() {
        while (m_IsStart) {
            float time = static_cast<float>(glfwGetTime());
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Collapsed) {
                for (Layer* l : m_LayerStack) {
                    l->OnUpdate(timestep);
                }
            }

            m_GuiLayer->Begin();
            for (Layer* l : m_LayerStack) {
                l->OnImGuiRender();
            }
            m_GuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    Application* CreateApplication() {
        return nullptr;
    }
} // namespace Engine

