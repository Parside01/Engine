#ifndef ENGINE_GUILAYER_HPP
#define ENGINE_GUILAYER_HPP

#include "../layer/Layer.hpp"
#include "../Application.hpp"

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
        float m_Time = 0.0f; 
    };
} // namespace Engine


#endif