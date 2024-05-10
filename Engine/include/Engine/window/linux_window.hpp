#ifndef ENGINE_LINUX_WINDOW_HPP
#define ENGINE_LINUX_WINDOW_HPP

#include "Window.hpp"
// #include "../engine_precompile_headers.hpp"
// #include "../Core.hpp"
// #include "../Utils.hpp"

// #include "../events/AppEvent.hpp"
// #include "../events/MouseEvent.hpp"
// #include "../events/KeyEvent.hpp"

#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Core.hpp"
#include "Engine/Utils.hpp"

#include "Engine/events/KeyEvent.hpp"
#include "Engine/events/MouseEvent.hpp"
#include "Engine/events/AppEvent.hpp"

#include "Engine/Render/OpenGL/RenderContext_OpenGL.hpp"

namespace Engine
{
    class LinuxWindow : public Window {
    public:

        LinuxWindow(const WindowProrepty& props);
        virtual ~LinuxWindow();

        void OnUpdate() override;

        inline uint32_t GetHeight() const override { return m_WindowData.Height; }
        inline uint32_t GetWidth() const override { return m_WindowData.Width; }
    
        void SetVsync(bool enabled) override;
        bool IsVsync() const override { return m_WindowData.Vsync; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { m_WindowData.EventCallback = callback; }

        inline void* GetNativeWindow() const override { return m_Window; }
    private:

        virtual void Init(const WindowProrepty& props);
        virtual void Shitdown();

    private:

        GLFWwindow* m_Window;
        RenderContext* m_Context;
        struct WindowData {
            std::string Title;
            uint32_t Width;
            uint32_t Height;
            bool Vsync;

            EventCallbackFn EventCallback;
        };

        WindowData m_WindowData;

    };
} // namespace Engine


#endif