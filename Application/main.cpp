#include "Engine/engine.hpp"

#include <glm/gtc/matrix_transform.hpp>

class TestLayer : public Engine::Layer {
public:
    TestLayer()
        : Layer("Test"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f), m_SquarePosition(0.f)
    {
        m_VertexArray.reset(Engine::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.f,
        };

        std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            Engine::BufferLayout layout = {
                {"a_Position", Engine::ShaderDataType::Float3},
                {"a_Color", Engine::ShaderDataType::Float4},
            };
            vertexBuffer->SetLayout(layout);
        }

        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<Engine::IndexBuffer> indexBuffer;
        indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        //// TESTING ////

        m_SquareVA.reset(Engine::VertexArray::Create());

        float blue_vertices[3 * 4] = {
            -0.75f, -0.75f, 0.70f,
             0.75f, -0.75f, 0.70f,
             0.75f,  0.75f, 0.70f,
            -0.75f,  0.75f, 0.70f,
        };

        std::shared_ptr<Engine::VertexBuffer> squareVB;
        squareVB.reset(Engine::VertexBuffer::Create(blue_vertices, sizeof(blue_vertices)));
        {
            squareVB->SetLayout({
                {"a_Position", Engine::ShaderDataType::Float3},
            });
        }
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t blue_indices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Engine::IndexBuffer> squareIB;
        squareIB.reset(Engine::IndexBuffer::Create(blue_indices, sizeof(blue_indices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        //// TESTING ////

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;
            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

        m_Shader = std::make_unique<Engine::Shader>(vertexSrc, fragmentSrc);


        //// TESTING ////
        std::string blue_vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main() {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

        blue_m_Shader.reset(new Engine::Shader(blue_vertexSrc, blue_fragmentSrc));

        //// TESTING ////
    }
    void OnUpdate(Engine::Timestep tick) override {
        if (Engine::Input::IsKeyPressed(EG_KEY_LEFT))
            m_CameraPosition.x += m_CameraSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_RIGHT))
            m_CameraPosition.x -= m_CameraSpeed * tick;

        if (Engine::Input::IsKeyPressed(EG_KEY_UP))
            m_CameraPosition.y -= m_CameraSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_DOWN))
            m_CameraPosition.y += m_CameraSpeed * tick;
        

        Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Engine::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);

        Engine::Renderer::BeginScene(m_Camera);
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.f), m_SquarePosition);

            Engine::Renderer::Submit(m_SquareVA, blue_m_Shader, transform);
            Engine::Renderer::Submit(m_VertexArray, m_Shader);
        }
        Engine::Renderer::EndScene();

    }

    virtual void OnImGuiRender() override
    {

    }

    void OnEvent(Engine::Event& event) override {
        Engine::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Engine::KeyPressedEvent>(EG_BINDEVENT(TestLayer::OnKeyPressed));
    }

    bool OnKeyPressed(Engine::KeyPressedEvent& event) {
        return false;
    }

private:
    std::shared_ptr<Engine::VertexArray> m_VertexArray;
    std::shared_ptr<Engine::Shader> m_Shader;

    std::shared_ptr<Engine::VertexArray> m_SquareVA;
    std::shared_ptr<Engine::Shader> blue_m_Shader;

    Engine::OrthCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed{1.f};

    glm::vec3 m_SquarePosition;
    float m_SquareSpeed{5.f};
};

class Sandbox : public Engine::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer);
    }
    ~Sandbox() {

    }
};

Engine::Application* Engine::CreateApplication() {
    return new Sandbox();
}