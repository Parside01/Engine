#ifndef ENGINE_SKYBOX_HPP
#define ENGINE_SKYBOX_HPP
#include <Engine/Render/Shader.hpp>
#include <Engine/Render/VertexArray.hpp>
#include <Engine/engine_precompile_headers.hpp>
#include <Engine/Render/Texture/Textures.hpp>
namespace Engine {
    class Skybox {
    private:
        Ref<Shader> mShader;
        Ref<CubeMap> mCubeMap;
    };
}

#endif //ENGINE_SKYBOX_HPP
