#include "Engine/Render/Texture/TextureManager.hpp"
#include "Engine/Render/OpenGL/TextureAtlas_OpenGL.hpp"
#include <Engine/Render/Texture/TextureTypes.hpp>
#include <stb_image.hpp>
#include <stb_image_resize2.hpp>
#include <Engine/Render/OpenGL/CubeMap_OpenGL.hpp>

#include "Engine/log/Log.hpp"


namespace Engine {
#ifdef ENGINE_API_OPENGL
    Scope<TextureAtlas> TextureManager::mTextureAtlas = std::make_unique<OpenGLTextureAtlas>(TextureTarget::TEXTURE2D, 2048, 2048, 4);
#endif
    // В 0 слоте лежит skybox.
    uint32_t TextureManager::mTextureSlotIndex = 1;

    void TextureManager::Init() {
        mTextureAtlas->Init();
    }

    Ref<Texture2D> TextureManager::CreateTexture(const std::string &path) {
        EG_PROFILE_FUNC();

        Ref<Texture2D> texture = LoadTexture(path);
        // ResizeTexture(texture->mWidth / 2, texture->mHeight / 2, texture);
        mTextureAtlas->AddTexture2D(texture);

        return texture;
    }

    Ref<Texture2D> TextureManager::CreateTexture(uint32_t width, uint32_t height, const glm::vec4 &color) {
        EG_PROFILE_FUNC();
        Ref<Texture2D> texture = std::make_shared<Texture2D>();
        texture->mHeight = height;
        texture->mWidth = width;
        texture->mChannelsNum = 4;
        texture->mTextureData.reset(new u_char[height * width * texture->mChannelsNum]);

        for (uint32_t i{0}; i < height * width; ++i) {
            texture->mTextureData[i * texture->mChannelsNum + 0] = color.r * 255;
            texture->mTextureData[i * texture->mChannelsNum + 1] = color.g * 255;
            texture->mTextureData[i * texture->mChannelsNum + 2] = color.b * 255;
            texture->mTextureData[i * texture->mChannelsNum + 3] = color.a * 255;
        }
        texture->mTextureHash = std::hash<std::string_view>()(std::string_view(
            reinterpret_cast<const char *>(texture->mTextureData.get()),
            texture->mHeight * texture->mWidth * texture->mChannelsNum));
        // Если что можно включить.
        // ResizeTexture(width / 2, height / 2, texture);
        mTextureAtlas->AddTexture2D(texture);

        return texture;
    }

    Ref<CubeMap> TextureManager::CreateCubeMap(const std::array<const std::string, 6>& paths) {
        std::array<Ref<Texture2D>, 6> textures;
        for (uint32_t i{0}; i < 6; ++i) {
            textures[i] = LoadTexture(paths[i]);
        }

#ifdef ENGINE_API_OPENGL
#include <Engine/Render/OpenGL/CubeMap_OpenGL.hpp>
        Ref<CubeMap> res = std::make_shared<OpenGLCubeMap>(textures);
        return res;
#endif
    }

    void TextureManager::ResizeTexture(uint32_t newWidth, uint32_t newHeight, Ref<Texture2D> &texture) {
        EG_PROFILE_FUNC();

        u_char *newData = new u_char[newHeight * newWidth * texture->mChannelsNum];
        stbir_resize(texture->mTextureData.get(), texture->mWidth, texture->mHeight, texture->mWidth * texture->mChannelsNum,
                     newData,
                     newWidth, newHeight, newWidth * texture->mChannelsNum, stbir_pixel_layout::STBIR_RGBA,
                     STBIR_TYPE_UINT8, STBIR_EDGE_CLAMP, STBIR_FILTER_BOX);

        texture->mTextureData.reset(newData);
        texture->mHeight = newHeight;
        texture->mWidth = newWidth;
        texture->mTextureHash = std::hash<std::string_view>()(
            std::string_view(reinterpret_cast<const char *>(newData), newWidth * newHeight * texture->mChannelsNum));
    }

    void TextureManager::BindTextures() {
        mTextureAtlas->Bind(mTextureSlotIndex);
    }


    // Может я тупой, но тут для кажого api надо поотедльности счиать, сейчас эта штука насктроена на opengl, для imgui надо менять (Как в ContentBrowser)
    std::array<glm::vec2, 4> TextureManager::GetTextureCoords(const Ref<Texture2D> &texture) {
        const glm::vec4 &coords = mTextureAtlas->GetTextureCoords(texture->mTextureHash);
        std::array<glm::vec2, 4> res = {
            glm::vec2(coords.x, coords.w),
            glm::vec2(coords.z, coords.w),
            glm::vec2(coords.z, coords.y),
            glm::vec2(coords.x, coords.y),
        };
        return res;
    }

    // Пока эта штука воозвращает просто 1, но потом, когда будет не один атлас, а несколько, то все будет иначе.
    uint32_t TextureManager::GetTextureSlot(const Ref<Texture2D> &texture) {
        return 1;
    }

    Ref<Texture2D> TextureManager::LoadTexture(const std::string &path) {
        EG_PROFILE_FUNC();
        int width, height, channels;
        Ref<Texture2D> texture = std::make_shared<Texture2D>();

        u_char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (!data) {
            EG_CORE_ERROR("Не удалось загрузить текстуру из {0}", path);
            EG_CORE_ASSERT(false);
            return nullptr;
        }

        texture->mChannelsNum = channels;
        texture->mHeight = height;
        texture->mWidth = width;
        texture->mTextureData.reset(data);

        texture->mTextureHash = std::hash<std::string_view>()(
            std::string_view(reinterpret_cast<const char *>(data),
                             texture->mHeight * texture->mWidth * texture->mChannelsNum));

        return texture;
    }
}
