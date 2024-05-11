#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

namespace Engine
{
    enum class RendererAPI {
        None = 0, OpenGL = 1
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }
    private:
        static RendererAPI s_RendererAPI;
    };
} // namespace Engine


#endif