#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#include "CanvaLayer.hpp"


void CanvaLayer::OnAttach() {
}

void CanvaLayer::OnDetach() {
}

void CanvaLayer::OnEvent(Engine::Event &event) {
    m_CameraController.OnEvent(event);

    Engine::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Engine::MouseMovedEvent>(EG_BINDEVENT(CanvaLayer::OnMouseMoved));
}

void CanvaLayer::OnUpdate(Engine::Timestep tick) {
    m_CameraController.OnUpdate(tick);

    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
    {
        for (uint32_t i{0}; i < allQuad.size(); ++i) {
            Engine::Renderer2D::DrawQuad(allQuad[i], {0.1f, 0.1f}, m_Color);
        }
    }
    Engine::Renderer2D::EndScene();
}

void CanvaLayer::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_Color));

    if (ImGui::Button("Click me!")) {
        allQuad = std::vector<glm::vec2>();
    }
    ImGui::End();
}

bool CanvaLayer::OnMouseMoved(Engine::MouseMovedEvent &event){
    std::pair<float, float> pos{event.GetX(), event.GetY()};
    uint32_t height = Engine::Application::GetApplication().GetWindow().GetHeight();
    uint32_t  width = Engine::Application::GetApplication().GetWindow().GetWidth();

    float x = pos.first / (float)width;
    float y = pos.second / (float)height;

    x = x * 2 - 1;
    y = 1 - y * 2;
    allQuad.push_back({x, y});
    return false;
}

