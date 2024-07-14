#include "Layer2D.hpp"

#include <Engine/Render/OpenGL/Shader_OpenGL.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>
#include <imgui/imgui.h>

void Layer2D::OnAttach() {
    m_VertexArray = Engine::VertexArray::Create();
    float vertices[4 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    Engine::Ref<Engine::VertexBuffer> VB = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
    VB->SetLayout({
        { "a_Position", Engine::ShaderDataType::Float3 },
    });
    m_VertexArray->AddVertexBuffer(VB);

    uint32_t indeces[6] = {0, 1, 2, 2, 3, 0};
    Engine::Ref<Engine::IndexBuffer> IB;
    IB = Engine::IndexBuffer::Create(indeces, sizeof(indeces) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(IB);

    m_ColorShader = Engine::Shader::Create("assets/shaders/Layer2D.glsl");
}

void Layer2D::OnDetach() {
}

void Layer2D::OnEvent(Engine::Event &event) {
    m_CameraController.OnEvent(event);
}

void Layer2D::OnUpdate(Engine::Timestep tick) {
    m_CameraController.OnUpdate(tick);

    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    Engine::Renderer::BeginScene(m_CameraController.GetCamera());
    {
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_ColorShader)->Bind();
        std::dynamic_pointer_cast<Engine::OpenGLShader>(m_ColorShader)->SetUniformFloat4("u_Color", m_Color);
        Engine::Renderer::Submit(m_VertexArray, m_ColorShader, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
    }
    Engine::Renderer::EndScene();
}

void Layer2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Shader Color", glm::value_ptr(m_Color));
    ImGui::End();
}