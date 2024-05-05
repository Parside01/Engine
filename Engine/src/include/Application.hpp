#ifndef ENGINE_APPLICATION_HPP
#define ENGINE_APPLICATION_HPP

#include "../include/Core.hpp"
#include "../include/events/Event.hpp"
#include "../include/events/AppEvent.hpp"

#include "engine_precompile_headers.hpp"
#include "../include/Utils.hpp"
#include "../include/layer/Layer.hpp"
#include "../include/layer/LayerStack.hpp"
#include "../include/log/Log.hpp"
#include "../include/window/Window.hpp"

namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

    private:
        bool OnWindowClose(WindowCloseEvent& event);

        std::unique_ptr<Window> m_Window;
        bool m_IsStart = true;

        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
} // namespace Engine

#endif