#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Render/RenderCommand.hpp"
#include "Engine/Render/OpenGL/RendererAPI_OpenGL.hpp"


namespace Engine
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
} // namespace Engine
