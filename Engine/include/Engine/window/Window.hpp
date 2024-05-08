#ifndef ENGINE_WINDOWN_HPP
#define ENGINE_WINDOWN_HPP

// #include "../engine_precompile_headers.hpp"

// #include "../Core.hpp"
// #include "../events/Event.hpp"

#include "Engine/Core.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include "Engine/events/Event.hpp"

namespace Engine
{   
    struct WindowProrepty {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProrepty(const std::string& title = "Engine", uint32_t width = 1280, uint32_t height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class ENGINE_API Window {
    public:
        typedef std::function<void(Event&)> EventCallbackFn;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual bool IsVsync() const = 0;
        virtual void SetVsync(bool enabled) = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        static Window* Create(const WindowProrepty& props = WindowProrepty());

        virtual void* GetNativeWindow() const = 0;
    };
} // namespace Engine



#endif