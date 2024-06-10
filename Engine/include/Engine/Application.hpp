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

        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

        std::unique_ptr<Window> m_Window;
        GuiLayer* m_GuiLayer;
        bool m_IsStart = true;
        LayerStack m_LayerStack;

        static Application* m_Instance;
    };

    Application* CreateApplication();
} // namespace Engine

#endif