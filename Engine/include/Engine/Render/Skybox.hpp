#ifndef ENGINE_SKYBOX_HPP
#define ENGINE_SKYBOX_HPP
#include <Engine/Render/Shader.hpp>
#include <Engine/Render/VertexArray.hpp>
#include <Engine/engine_precompile_headers.hpp>
#include <Engine/Render/Texture/Textures.hpp>

#include <Engine/Scene/EditorCamera.hpp>

namespace Engine {
    class Skybox {
    public:
        Skybox(const std::string &path);

        virtual ~Skybox() = default;

        void Draw(const Ref<EditorCamera> &camera);

    private:
        Ref<Shader> mShader;
        Ref<VertexArray> mVertexArray;
        Ref<CubeMap> mCubeMap;
    };
}

#endif //ENGINE_SKYBOX_HPP
