// #include "../include/Application.hpp"
// #include "../include/Input.hpp"

#include "Engine/Application.hpp"
#include "Engine/input/Input.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>

namespace Engine
{
    Application* Application::m_Instance = nullptr; 

    Application::Application() {
        EG_ASSERT(!m_Instance, "Application is exist");
        m_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_GuiLayer = new GuiLayer();

        PushLayer(m_GuiLayer);

        m_Window->SetEventCallback(EG_BINDEVENT(Application::OnEvent));

        glewExperimental = GL_TRUE;
        glewInit();
    
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 position;
            out vec3 v_position;
            void main() {
                v_position = position;
                gl_Position = vec4(position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_position;
            void main() {
                color = vec4(v_position * 0.5 + 0.2, 0.0);
            }
        )";

        m_Shader = new Shader(vertexSrc, fragmentSrc);
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
        delete m_Shader;
    }

    void Application::Run() {
        while (m_IsStart) {
            
            m_Shader->Bind();

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

