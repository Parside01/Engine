#ifndef CANVALYAER_HPP
#define CANVALYAER_HPP

#include <Engine/engine.hpp>

class CanvaLayer : public Engine::Layer {
public:
    CanvaLayer() : m_CameraController(1280.f / 720.f) {}
    virtual ~CanvaLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnEvent(Engine::Event &event) override;
    virtual void OnUpdate(Engine::Timestep tick) override;
    virtual void OnImGuiRender() override;

    bool OnMouseMoved(Engine::MouseMovedEvent& event);

private:
    Engine::OrthCameraController m_CameraController;
    std::vector<glm::vec2> allQuad;
    glm::vec4 m_Color{0.0f, 0.0f, 0.0f, 1.0f};
};



#endif //CANVALYAER_HPP
