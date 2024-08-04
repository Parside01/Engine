#include <stb_image.hpp>
#include <stb_image_resize2.hpp>
#include <Engine/log/Log.hpp>

#include "Engine/Render/Texture/Textures.hpp"

namespace Engine {
    // Texture2D::Texture2D(const std::string &path) {
    //     int width, height, channels;
    //     u_char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    //     if (!data) {
    //         EG_CORE_ERROR("Не удалось прочитать текстуру из файла {0}", path);
    //         EG_CORE_ASSERT(false);
    //     }
    //
    //     mTextureData = data;
    //     mChannels = channels;
    //     mWidth = width;
    //     mHeight = height;
    //
    //     mTextureHash = std::hash<std::string_view>()(std::string_view(reinterpret_cast<const char*>(data), mWidth * mHeight * mChannels));
    //     mTextureID = mTextureHash;
    // }
    //
    // bool Texture2D::Resize(uint32_t width, uint32_t height) {
    //     u_char* resizeData = new u_char[width * height * mChannels];
    //
    // }

}
