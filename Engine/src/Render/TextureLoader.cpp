#include "Engine/Render/Texture/TextureSystemSketch.hpp"

namespace Engine {
    Ref<Texture2D> TextureLoader::LoadTexture2DFromFile(const std::filesystem::path& path) {
#ifdef ENGINE_API_OPENGL
        return std::make_shared<Texture2D_OpenGL>(path);
#elif ENGINE_API_VULKAN
#endif
    }

    Ref<Texture2D> TextureLoader::LoadTexture2DFromMemory(uint32_t width, uint32_t height, const u_char *data) {
#ifdef ENGINE_API_OPENGL
        return std::make_shared<Texture2D_OpenGL>(width, height, data);
#elif ENGINE_API_VULKAN
#endif
    }
}
