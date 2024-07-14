#ifndef LAYER2D_HPP
#define LAYER2D_HPP
#include <Engine/engine.hpp>


class Layer2D : public Engine::Layer {
public:
    Layer2D(): m_CameraController(1280.f / 720.f) {}
    virtual ~Layer2D() = default;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnEvent(Engine::Event &event) override;
    virtual void OnUpdate(Engine::Timestep tick) override;
    virtual void OnImGuiRender() override;

private:
    Engine::OrthCameraController m_CameraController;

    Engine::Ref<Engine::VertexArray> m_VertexArray;
    Engine::Ref<Engine::Shader> m_ColorShader;

    glm::vec4 m_Color{0.2f, 0.3f, 0.8f, 1};
};



#endif //LAYER2D_HPP
