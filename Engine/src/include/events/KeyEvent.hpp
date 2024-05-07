#ifndef ENGINE_KEYEVENT_HPP
#define ENGINE_KEYEVENT_HPP

#include "Event.hpp"

namespace Engine {
    
    class ENGINE_API KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

        int m_KeyCode;  
    };

    class ENGINE_API KeyPressedEvent : public KeyEvent {
    public :
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}
    
        inline int GetRepeatCount() const { return m_repeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent --- keycode: " << m_KeyCode << " repeatCount: " << m_repeatCount;

            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeatCount;
    };


    class ENGINE_API KeyReleasedEvent : public KeyEvent {
    public: 
        KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent --- keycode: " << m_KeyCode;
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyReleased)
    };

    class ENGINE_API KeyTypedEvent : public KeyEvent {
    public: 
        KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent --- keycode: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif