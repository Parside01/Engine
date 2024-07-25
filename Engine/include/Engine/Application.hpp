#ifndef ENGINE_APPLICATION_HPP
#define ENGINE_APPLICATION_HPP

#include "Engine/Core.hpp"
#include "Engine/GUI/GuiLayer.hpp"
#include "Engine/events/Event.hpp"
#include "Engine/events/AppEvent.hpp"
#include "Engine/Render/FrameBuffer.hpp"
#include "Engine/layer/Layer.hpp"
#include "Engine/layer/LayerStack.hpp"
#include "Engine/log/Log.hpp"
#include "Engine/window/Window.hpp"
#include "Engine/Timestep.hpp"


namespace Engine
{
    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& GetApplication() { return *m_Instance; }
        inline Window& GetWindow() const { return *m_Window; }
        inline GuiLayer& GetGuiLayer() const { return *m_GuiLayer; }
    private:

        bool OnWindowClose(WindowCloseEvent& event);
        bool OnWindowResize(WindowResizeEvent& event);

    private:

        Scope<Window> m_Window;

        GuiLayer* m_GuiLayer;
        bool m_IsStart{true};
        bool m_Collapsed{false};
        LayerStack m_LayerStack;
        Timestep m_Timestep; 
        float m_LastFrameTime{0.0f};
    private:
        static Application* m_Instance;
    };

    Application* CreateApplication();
} // namespace Engine

#endif