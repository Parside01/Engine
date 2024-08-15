#ifndef ENGINE_MESHMANAGER_HPP
#define ENGINE_MESHMANAGER_HPP

#include "Engine/Render/Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Engine {

    class MeshManager {
    public:
        static Ref<Mesh> CreateMesh(const std::string& path);

    private:
        static void InitMesh(const aiScene* scene, Ref<Mesh>& mesh);
        static void CountVerticesAndMeshes(const aiScene* scene, Ref<Mesh>& mesh);
        static void ReserveMeshSpace(const aiScene* scene, Ref<Mesh>& mesh);
        static void InitAllNestedMeshes(const aiScene* scene, Ref<Mesh>& mesh);
        static void InitNestedMesh(const aiMesh* nested, Ref<Mesh>& mesh);
    };

}

#endif //ENGINE_MESHMANAGER_HPP
