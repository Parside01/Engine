#include "Engine/Render/Texture.hpp"
#include "Engine/Render/Renderer.hpp"
#include "Engine/Render/OpenGL/Texture_OpenGL.hpp"

namespace Engine {

    Ref<Texture2D> Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: EG_CORE_ASSERT(false, "RendererAPI::None is not support");
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

}
