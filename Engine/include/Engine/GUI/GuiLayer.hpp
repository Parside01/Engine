#ifndef ENGINE_GUILAYER_HPP
#define ENGINE_GUILAYER_HPP

// #include "../layer/Layer.hpp"
// #include "../events/Event.hpp"
// #include "../events/KeyEvent.hpp"
// #include "../events/AppEvent.hpp"
// #include "../events/MouseEvent.hpp"
// #include "../Utils.hpp"

// #include "../Application.hpp"

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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        virtual void OnEvent(Event& event);

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }
        void SetDarkTheme();

        uint32_t GetActiveWidgetID() const;
    private:
        bool m_BlockEvents = true; 
    };
} // namespace Engine


#endif