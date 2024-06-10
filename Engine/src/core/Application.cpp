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
        m_Window->SetEventCallback(EG_BINDEVENT(Application::OnEvent));

        glewExperimental = GL_TRUE;
        glewInit();
        
        m_GuiLayer = new GuiLayer();
        PushOverlay(m_GuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.f, 0.f, 1.f, 1.f,
             0.5f, -0.5f, 0.0f, 1.f, 0.f, 1.f, 1.f,
             0.0f,  0.5f, 0.0f, 1.f, 0.f, 1.f, 1.f,
        };


        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                {"a_Position", ShaderDataType::Float3},
                {"a_Normal", ShaderDataType::Float3},
                {"a_Color", ShaderDataType::Float4},
            };
            m_VertexBuffer->SetLayout(layout);
        }

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            out vec3 v_Position;
            out vec4 v_Color;
            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position * 0.5, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            in vec4 v_Color;
            void main() {
                color = vec4(v_Position, 0.0);
                color = v_Color;
            }
        )";

        m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
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

    void Application::Run() {
        while (m_IsStart) {
            
            m_Shader->Bind();
            m_VertexArray->Bind();

            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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

