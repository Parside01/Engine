#ifndef ENGINE_TEXTURE2D_OPENGL_HPP
#define ENGINE_TEXTURE2D_OPENGL_HPP

#include "Engine/Render/Texture/Textures.hpp"

namespace Engine {
#if 0
    class Texture2D_OpenGL : public Texture2D {
    public:

        Texture2D_OpenGL(const std::filesystem::path& path);
        Texture2D_OpenGL(uint32_t width, uint32_t height, const u_char* data);
        virtual ~Texture2D_OpenGL();

    private:

        virtual void Bind(uint32_t slot = 0) const;
        virtual void Unbind() const;

        u_char* GetDataFromImage(const std::filesystem::path& path);
        void CreateTextureAndSetData(const u_char* textureData);

    private:
        uint32_t mFormat;
        uint32_t mInternalFormat;
    };
#endif
}

#endif //ENGINE_TEXTURE2D_OPENGL_HPP
