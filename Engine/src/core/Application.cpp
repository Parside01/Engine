// #include "../include/Application.hpp"
// #include "../include/Input.hpp"

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

        glewExperimental = GL_TRUE;
        glewInit();

        m_GuiLayer = new GuiLayer();
        PushOverlay(m_GuiLayer); 
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
    float val{0.f}, inc{0.05f};
    void Application::Run() {
        while (m_IsStart) {
            
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time; 

            for (Layer* l : m_LayerStack) {
                l->OnUpdate(timestep);
            }
            // m_GuiLayer->Begin();
            // for (Layer* l : m_LayerStack) {
            //     l->OnImGuiRender();
            // }
            // m_GuiLayer->End();
            
            m_Window->OnUpdate();
        }
    }

    Application* CreateApplication() {
        return nullptr;
    }
} // namespace Engine

