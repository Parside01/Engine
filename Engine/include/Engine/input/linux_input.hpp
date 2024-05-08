#ifndef ENGINE_LINUX_INPUT_HPP
#define ENGINE_LINUX_INPUT_HPP

// #include "../Input.hpp"
// #include "../Application.hpp"

#include "Engine/input/Input.hpp"
#include "Engine/Application.hpp"

namespace Engine
{
    class WindowsInput : public Input {
    protected:

        virtual bool IsKeyPressed_Impl(int keyCode) override;

        virtual bool IsMouseButtonPressed_Impl(int button) override;

        virtual std::pair<float, float> GetMousePosition_Impl() override;
        virtual float GetMouseX_Impl() override;
        virtual float GetMouseY_Impl() override;

    };
} // namespace Engine


#endif