#include "Engine/Render/Texture/TextureManager.hpp"
#include "Engine/Render/OpenGL/TextureAtlas_OpenGL.hpp"

#include <stb_image.hpp>
#include <stb_image_resize2.hpp>

#include "Engine/log/Log.hpp"


namespace Engine {
#ifdef ENGINE_API_OPENGL
    Scope<TextureAtlas> TextureManager::mTextureAtlas = std::make_unique<OpenGLTextureAtlas>(2048, 2048, 4);
#endif
    uint32_t TextureManager::mTextureSlotIndex = 0;

    void TextureManager::Init() {
        mTextureAtlas->Init();
    }

    Ref<Texture2D> TextureManager::CreateTexture(const std::string &path) {
        EG_PROFILE_FUNC();
        int width, height, channels;
        u_char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data) {
            EG_CORE_ERROR("Не удалось загрузить текстуру из {0}", path);
            EG_CORE_ASSERT(false);
            return nullptr;
        }

        Ref<Texture2D> texture = std::make_shared<Texture2D>();
        texture->Channels = channels;
        texture->Height = height;
        texture->Width = width;
        texture->TextureData.reset(data);

        texture->TextureHash = std::hash<std::string_view>()(
            std::string_view(reinterpret_cast<const char *>(data),
                             texture->Height * texture->Width * texture->Channels));
        // Если что можно включить.
        // ResizeTexture(width / 2, height / 2, texture);
        mTextureAtlas->AddTexture(texture);

        return texture;
    }

    Ref<Texture2D> TextureManager::CreateTexture(uint32_t width, uint32_t height, const glm::vec4 &color) {
        EG_PROFILE_FUNC();
        Ref<Texture2D> texture = std::make_shared<Texture2D>();
        texture->Height = height;
        texture->Width = width;
        texture->Channels = 4;
        texture->TextureData.reset(new u_char[height * width * texture->Channels]);

        for (uint32_t i{0}; i < height * width; ++i) {
            texture->TextureData[i * texture->Channels + 0] = color.r * 255;
            texture->TextureData[i * texture->Channels + 1] = color.g * 255;
            texture->TextureData[i * texture->Channels + 2] = color.b * 255;
            texture->TextureData[i * texture->Channels + 3] = color.a * 255;
        }
        texture->TextureHash = std::hash<std::string_view>()(std::string_view(
            reinterpret_cast<const char *>(texture->TextureData.get()),
            texture->Height * texture->Width * texture->Channels));
        // Если что можно включить.
        // ResizeTexture(width / 2, height / 2, texture);
        mTextureAtlas->AddTexture(texture);

        return texture;
    }


    void TextureManager::ResizeTexture(uint32_t newWidth, uint32_t newHeight, Ref<Texture2D> &texture) {
        EG_PROFILE_FUNC();

        u_char *newData = new u_char[newHeight * newWidth * texture->Channels];
        stbir_resize(texture->TextureData.get(), texture->Width, texture->Height, texture->Width * texture->Channels,
                     newData,
                     newWidth, newHeight, newWidth * texture->Channels, stbir_pixel_layout::STBIR_RGBA,
                     STBIR_TYPE_UINT8, STBIR_EDGE_CLAMP, STBIR_FILTER_BOX);

        texture->TextureData.reset(newData);
        texture->Height = newHeight;
        texture->Width = newWidth;
        texture->TextureHash = std::hash<std::string_view>()(
            std::string_view(reinterpret_cast<const char *>(newData), newWidth * newHeight * texture->Channels));
    }

    void TextureManager::BindTextures() {
        mTextureAtlas->Bind(mTextureSlotIndex);
    }


    // Может я тупой, но тут для кажого api надо поотедльности счиать, сейчас эта штука насктроена на opengl, для imgui надо менять (Как в ContentBrowser)
    std::array<glm::vec2, 4> TextureManager::GetTextureCoords(const Ref<Texture2D> &texture) {
        const glm::vec4 &coords = mTextureAtlas->GetTextureCoords(texture->TextureHash);
        std::array<glm::vec2, 4> res = {
            glm::vec2(coords.x, coords.w),
            glm::vec2(coords.z, coords.w),
            glm::vec2(coords.z, coords.y),
            glm::vec2(coords.x, coords.y),
        };
        return res;
    }

    // Пока эта штука воозвращает просто 0, но потом, когда будет не один атлас, а несколько, то все будет иначе.
    uint32_t TextureManager::GetTextureSlot(const Ref<Texture2D> &texture) {
        return 0;
    }
}
