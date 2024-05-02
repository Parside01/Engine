#ifndef ENGINE_MOUSEEVENT_HPP
#define ENGINE_MOUSEEVENT_HPP

#include "Event.hpp"
#include <strstream>

namespace Engine
{
    class ENGINE_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent --- x: " << m_MouseX << " y: " << m_MouseY;
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_MouseX;
        float m_MouseY;
    };
} // namespace Engine


#endif