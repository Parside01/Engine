#ifndef ENGINE_GUILAYER_HPP
#define ENGINE_GUILAYER_HPP

// #include "../layer/Layer.hpp"
// #include "../events/Event.hpp"
// #include "../events/KeyEvent.hpp"
// #include "../events/AppEvent.hpp"
// #include "../events/MouseEvent.hpp"
// #include "../Utils.hpp"

// #include "../Application.hpp"

#include "Engine/Application.hpp"
#include "Engine/layer/Layer.hpp"
#include "Engine/events/Event.hpp"
#include "Engine/events/KeyEvent.hpp"
#include "Engine/events/MouseEvent.hpp"
#include "Engine/events/AppEvent.hpp"

namespace Engine
{
    class ENGINE_API GuiLayer : public Layer {
    public:

        GuiLayer();
        ~GuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    
    private:

        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
        bool OnMouseScrolledEvent(MouseScrolledEvent& event);
        bool OnMouseMovedEvent(MouseMovedEvent& event);

        bool OnKeyPressedEvent(KeyPressedEvent& event);
        bool OnKeyReleasedEvent(KeyReleasedEvent& event);
        bool OnKeyTypedEvent(KeyTypedEvent& event);

        bool OnWindowResizeEvent(WindowResizeEvent& event);
    
    private:
        float m_Time = 0.0f; 
    };
} // namespace Engine


#endif