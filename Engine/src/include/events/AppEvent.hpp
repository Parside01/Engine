#ifndef ENGINE_APPEVENT_HPP
#define ENGINE_APPEVENT_HPP

#include <sstream>

#include "../include/Core.hpp"
#include "Event.hpp"

namespace Engine {

    class ENGINE_API WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(uint32_t width, uint16_t height)
            : m_Width(width), m_Height(height) {}

        inline uint32_t GetWidth() const { return m_Width; }
        inline uint16_t GetHeight() const { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss; 
            ss << "WindowResizeEvent --- wth: " << m_Width << " hth: " << m_Height;

            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        uint32_t m_Width;
        uint16_t m_Height;
    };

    class ENGINE_API WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ENGINE_API AppTickEvent : public Event {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ENGINE_API AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class ENGINE_API AppRenderEvent : public Event {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };  
}

#endif
