#ifndef ENGINE_MESH_HPP
#define ENGINE_MESH_HPP

#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>

#include "Texture/Textures.hpp"

namespace Engine {

    struct Vertex3D {
        glm::vec3 Position;
        glm::vec4 Color;
        // glm::vec2 TextureCoord;
        // float TextureIndex;
        int EntityID = -1;
    };

    class Mesh {
    public:
        Mesh(const std::vector<Vertex3D>& vertices, const std::vector<uint32_t>& indices/*, const std::vector<Ref<Texture3D>>& textures*/)
            : mVertices(vertices), mIndices(indices) /*mTextures(textures)*/ {}

        const std::vector<Vertex3D>& GetVertices() const { return mVertices; }
        const std::vector<uint32_t>& GetIndeces() const { return mIndices; }

    private:
        std::vector<Vertex3D> mVertices;
        std::vector<uint32_t> mIndices;
        // std::vector<Ref<Texture3D>> mTextures;
    };

}

#endif //ENGINE_MESH_HPP
