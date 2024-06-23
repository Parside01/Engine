#ifndef ENGINE_APPLICATION_HPP
#define ENGINE_APPLICATION_HPP

#include "Engine/Core.hpp"
#include "Engine/GUI/GuiLayer.hpp"
#include "Engine/events/Event.hpp"
#include "Engine/events/AppEvent.hpp"
#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Utils.hpp"
#include "Engine/layer/Layer.hpp"
#include "Engine/layer/LayerStack.hpp"
#include "Engine/log/Log.hpp"
#include "Engine/window/Window.hpp"

#include "Engine/Render/OpenGL/Shader.hpp"
#include "Engine/Render/Buffers.hpp"
#include "Engine/Render/VertexArray.hpp"

#include "Engine/Render/OrthCamera.hpp"


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

        inline static Application& GetApplication() { return *m_Instance; }
        inline Window& GetWindow() const { return *m_Window; }

    private:
        bool OnWindowClose(WindowCloseEvent& event);

    private:
        static Application* m_Instance;
        std::unique_ptr<Window> m_Window;
        GuiLayer* m_GuiLayer;
        bool m_IsStart = true;
        LayerStack m_LayerStack;

    };

    Application* CreateApplication();
} // namespace Engine

#endif