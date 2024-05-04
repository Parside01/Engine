#ifndef ENGINE_APPLICATION_HPP
#define ENGINE_APPLICATION_HPP

#include "../include/Core.hpp"
#include "engine_precompile_headers.hpp"
#include "../include/window/Window.hpp"

namespace Engine
{
    class ENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_IsStart = true;
    };

    Application* CreateApplication();
} // namespace Engine

#endif