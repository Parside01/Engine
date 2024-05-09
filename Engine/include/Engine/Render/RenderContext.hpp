#ifndef ENGINE_RENDERCONTEXT_HPP
#define ENGINE_RENDERCONTEXT_HPP

#include "Engine/Core.hpp"

namespace Engine
{
    class ENGINE_API RenderContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
} // namespace Engine


#endif