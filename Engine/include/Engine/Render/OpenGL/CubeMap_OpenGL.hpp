#ifndef ENGINE_CUBEMAP_OPENGL_HPP
#define ENGINE_CUBEMAP_OPENGL_HPP
#ifdef ENGINE_API_OPENGL
#include <Engine/Render/Texture/Textures.hpp>
namespace Engine {

    class OpenGLCubeMap : public CubeMap {
    public:
        OpenGLCubeMap(const std::array<Ref<Texture2D>, 6>);
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual uint32_t GetTextureID() const override { return mTextureID; }

    private:
        uint32_t mTextureID;
    };
}

#endif
#endif //ENGINE_CUBEMAP_OPENGL_HPP
