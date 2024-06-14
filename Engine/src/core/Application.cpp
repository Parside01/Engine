// #include "../include/Application.hpp"
// #include "../include/Input.hpp"

#include "Engine/Application.hpp"
#include "Engine/input/Input.hpp"
#include "Engine/Render/RenderCommand.hpp"
#include "Engine/Render/Renderer.hpp"

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
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.f,
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                {"a_Position", ShaderDataType::Float3},
                {"a_Color", ShaderDataType::Float4},
            };
            vertexBuffer->SetLayout(layout);
        }

        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        //// TESTING ////

        m_SquareVA.reset(VertexArray::Create());

        float blue_vertices[3 * 4] = {
            -0.75f, -0.75f, 0.70f, 
             0.75f, -0.75f, 0.70f, 
             0.75f,  0.75f, 0.70f, 
            -0.75f,  0.75f, 0.70f, 
        };

        std::shared_ptr<VertexBuffer> squareVB; 
        squareVB.reset(VertexBuffer::Create(blue_vertices, sizeof(blue_vertices)));
        {
            squareVB->SetLayout({
                {"a_Position", ShaderDataType::Float3},
            });
        }
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t blue_indices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB; 
        squareIB.reset(IndexBuffer::Create(blue_indices, sizeof(blue_indices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        //// TESTING ////

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            out vec3 v_Position;
            out vec4 v_Color;
            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            in vec4 v_Color;
            void main() {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);


        //// TESTING ////
        std::string blue_vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            out vec3 v_Position;
        
            void main() {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string blue_fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            void main() {
                color = vec4(0.2, 0.3, 0.8, 0.2);
            }
        )";

        blue_m_Shader.reset(new Shader(blue_vertexSrc, blue_fragmentSrc));

        //// TESTING ////
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
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
            RenderCommand::Clear();
            
            Renderer::BeginScene();
            {
                blue_m_Shader->Bind();
                Renderer::Submit(m_SquareVA);

                m_Shader->Bind();
                Renderer::Submit(m_VertexArray);
            }
            Renderer::EndScene();

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

