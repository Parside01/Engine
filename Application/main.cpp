#include "include/engine.hpp"

class TestLayer : public Engine::Layer {
public:
    TestLayer() : Layer("Test") {}
    void OnUpdate() override {
        EG_INFO("TestLayer::OnUpdate");
    }

    void OnEvent(Engine::Event& event) override {
        EG_INFO("TestLayer::OnEvent -> {0}", event.ToString());
    }
};

class Sandbox : public Engine::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer());
    }
    ~Sandbox() {

    }
};

Engine::Application* Engine::CreateApplication() {
    return new Sandbox();
}