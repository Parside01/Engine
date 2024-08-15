#ifndef ENGINE_MESH_HPP
#define ENGINE_MESH_HPP

#include "Engine/engine_precompile_headers.hpp"
#include <glm/glm.hpp>

#include "Texture/Textures.hpp"


namespace Engine {

    struct Vertex3D {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TextureCoord;
        glm::vec3 Normal;
        // float TextureIndex;
        int EntityID = -1;
    };

    class Mesh {
        friend class MeshManager;
    public:
        Mesh() = default;
        struct NestedMesh {
            uint32_t mNumIndices = 0;
            uint32_t mNumVertices = 0;
            uint32_t mBaseVertex = 0;
            uint32_t mBaseIndex = 0;
            uint32_t mMaterialIndex = 0;
        };

        const std::vector<Vertex3D>& GetVertices() const { return mVertices; }
        const std::vector<uint32_t>& GetIndices() const { return mIndices; }
        const std::vector<NestedMesh>& GetNestedMeshes() const { return mNestedMeshes; }

    private:

        uint32_t mNumVertices = 0;
        uint32_t mNumIndices = 0;

        std::vector<Vertex3D> mVertices;
        std::vector<uint32_t> mIndices;
        // std::vector<Ref<Texture3D>> mTextures;
        std::vector<NestedMesh> mNestedMeshes;
    };

}


#endif //ENGINE_MESH_HPP
