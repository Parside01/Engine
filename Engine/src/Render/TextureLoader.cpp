#include <Engine/Utils.hpp>
#include "Engine/Render/Texture/TextureLoader.hpp"
#include "Engine/Render/Texture/Textures.hpp"

namespace Engine {
    TextureManager TextureLoader::sTextureManager = TextureManager();

    Ref<Texture2D> TextureLoader::LoadTexture2DFromFile(const std::filesystem::path& path) {
#ifdef ENGINE_API_OPENGL
        return sTextureManager.CreateTexture(path.string());
#elif ENGINE_API_VULKAN
#endif
    }

//     Ref<Texture2D> TextureLoader::LoadTexture2DFromColor(uint32_t width, uint32_t height, const glm::vec4& color) {
//         u_char* texureData = reinterpret_cast<u_char*>(Utils::GetColor(color));
//         return LoadTexture2DFromMemory(width, height, texureData);
//     }
//
//     Ref<Texture2D> TextureLoader::LoadTexture2DFromMemory(uint32_t width, uint32_t height, const u_char *data) {
// #ifdef ENGINE_API_OPENGL
//         return std::make_shared<>(width, height, data);
// #elif ENGINE_API_VULKAN
// #endif
//     }
}
