#ifndef LAYER2D_HPP
#define LAYER2D_HPP
#include <Engine/engine.hpp>
#include <imgui/imgui.h>
#include "ImGuizmo.h"


class Layer2D : public Engine::Layer {
public:
    Layer2D(): Layer("Layer2D"), m_CameraController(1280.f / 720.f), m_ViewportSize(1280, 720), m_MainScene(std::make_shared<Engine::Scene>()), m_EntityBrowser(m_MainScene), m_EditorCamera(45.f, 1280.f / 720.f, 0.1f, 10000.f) {}
    virtual ~Layer2D() = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnEvent(Engine::Event &event) override;
    virtual void OnUpdate(Engine::Timestep tick) override;
    virtual void OnImGuiRender() override;

    bool OnMouseButtonPressed(Engine::MouseButtonPressedEvent& event);

private:
    glm::vec2 m_ViewportBounds[2] = { {0.0f, 0.0f}, {1280.0f, 720.0f} };
    glm::vec2 m_ViewportSize;
    bool m_ViewportFocused{false}, m_ViewportHovered{false};

    int m_GuizmoOperation;

    float Tick{1.0f};

    Engine::Entity m_ESquere;
    Engine::Entity m_ECamera;
    Engine::Entity m_EQuad; 

    Engine::Entity m_HoveredEntity;

    Engine::Ref<Engine::Scene> m_MainScene;

    Engine::EditorCamera m_EditorCamera; 
    Engine::EntityBrowser m_EntityBrowser;
    Engine::ContentBrowser m_ContentBrowser;

    Engine::OrthCameraController m_CameraController;
    Engine::Ref<Engine::FrameBuffer> m_Framebuffer;
    Engine::Ref<Engine::Texture2D> m_Texture2D; 
};



#endif //LAYER2D_HPP
