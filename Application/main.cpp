#include "Engine/engine.hpp"

class TestLayer : public Engine::Layer {
public:
    TestLayer() : Layer("Test") {}
    void OnUpdate() override {
        if (Engine::Input::IsKeyPressed(EG_KEY_TAB)) {
        
        }
    }

    void OnEvent(Engine::Event& event) override {
    }
};

class Sandbox : public Engine::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer);
        PushOverlay(new Engine::GuiLayer);
    }
    ~Sandbox() {

    }
};

Engine::Application* Engine::CreateApplication() {
    return new Sandbox();
}