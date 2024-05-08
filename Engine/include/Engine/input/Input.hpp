#ifndef ENGINE_INPUT_HPP
#define ENGINE_INPUT_HPP

// #include "Core.hpp"
// #include "events/Event.hpp"

#include "Engine/Core.hpp"
#include "Engine/events/Event.hpp"

namespace Engine
{
    class ENGINE_API Input {
    public:

        inline static bool IsKeyPressed(int keyCode) { return s_Instanse->IsKeyPressed_Impl(keyCode); }

        inline static bool IsMouseButtonPressed(int button) { return s_Instanse->IsMouseButtonPressed_Impl(button); } 
        inline static float GetMouseX() { return s_Instanse->GetMouseX_Impl(); } 
        inline static float GetMouseY() { return s_Instanse->GetMouseY_Impl(); }
        inline static std::pair<float, float> GetMousePosition() { return s_Instanse->GetMousePosition_Impl(); }
    protected:

        virtual bool IsKeyPressed_Impl(int keyCode) = 0;

        virtual bool IsMouseButtonPressed_Impl(int button) = 0;

        virtual std::pair<float, float> GetMousePosition_Impl() = 0;
        virtual float GetMouseX_Impl() = 0;
        virtual float GetMouseY_Impl() = 0;

    private:

        static Input* s_Instanse;
    };
} // namespace Engine


#endif