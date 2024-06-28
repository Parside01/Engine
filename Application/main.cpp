#include "imgui/imgui.h"
#include "Engine/engine.hpp"
#include "Engine/Render/OpenGL/Shader_OpenGL.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class TestLayer : public Engine::Layer {
public:
    TestLayer()
        : Layer("Test"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.f), m_CubePosition(0.f)
    {
        m_VertexArray.reset(Engine::VertexArray::Create());

        float vertices[3 * 8 + 2 * 8] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
        };

        Engine::Ref<Engine::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            Engine::BufferLayout layout = {
                {"a_Position", Engine::ShaderDataType::Float3},
                {"a_TexCoord", Engine::ShaderDataType::Float2},
            };
            vertexBuffer->SetLayout(layout);
        }

        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[36] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            0, 4, 5, 5, 1, 0,
            1, 5, 6, 6, 2, 1,
            2, 6, 7, 7, 3, 2,
            3, 7, 4, 4, 0, 3,
        };
        Engine::Ref<Engine::IndexBuffer> indexBuffer;
        indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // Main cube shader //
        const std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;

            void main() {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        const std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            uniform vec3 u_Color;
            in vec2 v_TexCoord;
            uniform sampler2D u_Texture;

            void main() {
                color = texture(u_Texture, v_TexCoord);
            }
        )";

        m_CubeShader.reset(Engine::Shader::Create("assets/shaders/cube.glsl"));
        // Main cube shader //

        m_CubeTexture = Engine::Texture2D::Create("assets/textures/ChessBoard.jpeg");
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_CubeShader)->SetUniformInt("u_Texture", 0);
    }

    void OnUpdate(Engine::Timestep tick) override {
        if (Engine::Input::IsKeyPressed(EG_KEY_W))
            m_CubeRotation.x -= m_CubeRotationSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_S))
            m_CubeRotation.x += m_CubeRotationSpeed * tick;

        if (Engine::Input::IsKeyPressed(EG_KEY_A))
            m_CubeRotation.y -= m_CubeRotationSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_D))
            m_CubeRotation.y += m_CubeRotationSpeed * tick;

        if (Engine::Input::IsKeyPressed(EG_KEY_RIGHT))
            m_CameraPosition.x += m_CameraSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_LEFT))
            m_CameraPosition.x -= m_CameraSpeed * tick;

        if (Engine::Input::IsKeyPressed(EG_KEY_UP))
            m_CameraPosition.y += m_CameraSpeed * tick;
        else if (Engine::Input::IsKeyPressed(EG_KEY_DOWN))
            m_CameraPosition.y -= m_CameraSpeed * tick;


        Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Engine::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_CubeShader)->Bind();
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_CubeShader)->SetUniformFloat3("u_Color", m_CubeFacetsColor);

        Engine::Renderer::BeginScene(m_Camera);
        {
            glm::mat4 transfrom = glm::translate(glm::mat4(1.f), m_CubePosition);
            transfrom = glm::rotate(transfrom, -glm::radians(m_CubeRotation.x), glm::vec3(1.f, 0.f, 0.f));
            transfrom = glm::rotate(transfrom, -glm::radians(m_CubeRotation.y), glm::vec3(0.f, 1.f, 0.f));
            Engine::Renderer::Submit(m_VertexArray, m_CubeShader, transfrom);

            m_CubeTexture->Bind();
            Engine::Renderer::Submit(m_VertexArray, m_CubeShader, transfrom);
        }
        Engine::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Color settings");

        ImGui::ColorEdit3("Cube Facets Color", glm::value_ptr(m_CubeFacetsColor));

        ImGui::End();
    }

    void OnEvent(Engine::Event& event) override {
        Engine::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Engine::KeyPressedEvent>(EG_BINDEVENT(TestLayer::OnKeyPressed));
    }

    bool OnKeyPressed(Engine::KeyPressedEvent& event) {
        return false;
    }

private:
    Engine::Ref<Engine::VertexArray> m_VertexArray;
    Engine::Ref<Engine::Shader> m_CubeShader;

    Engine::OrthCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed{2.f};

    Engine::Ref<Engine::Texture2D> m_CubeTexture;
    glm::vec3 m_CubePosition;
    glm::vec2 m_CubeRotation;
    float m_CubeRotationSpeed{20.f};
    glm::vec3 m_CubeFacetsColor = { 0.2f, 0.3f, 0.8f };
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