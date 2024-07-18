#include "Layer2D.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <imgui/imgui.h>


void Layer2D::OnAttach() {
    m_Texture2D = Engine::Texture2D::Create("assets/textures/ChessBoard.jpeg");
}

void Layer2D::OnDetach() {
    
}

void Layer2D::OnEvent(Engine::Event &event) {
    EG_PROFILE_FUNC();
    m_CameraController.OnEvent(event);
}

void Layer2D::OnUpdate(Engine::Timestep tick) {
    EG_PROFILE_FUNC();

    {
        EG_PROFILE_SCOPE("m_CameraController.OnUpdate");
        m_CameraController.OnUpdate(tick);
    }
    
    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        EG_PROFILE_SCOPE("Renderer 2DScene");
        glm::vec2 pos{0.f, 0.f};
        glm::vec2 size{1.f, 1.f};
        glm::vec4 color{0.8f, 0.2f, 0.3f, 1.0f};
        Engine::Renderer2D::DrawQuad(pos, size, color);
    }
    Engine::Renderer2D::EndScene();
}

void Layer2D::OnImGuiRender() {
    EG_PROFILE_FUNC();
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Shader Color", glm::value_ptr(m_Color));
    ImGui::End();
}