#include "Engine/Render/MeshManager.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Engine/log/Log.hpp>

namespace Engine {

    Ref<Mesh> MeshManager::CreateMesh(const std::string &path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            EG_CORE_ERROR("Не удалось загузить модель из файла {0}", path);
            EG_CORE_ASSERT(false);
            return nullptr;
        }

        std::vector<Vertex3D> vertices;
        std::vector<uint32_t> indeces;
        // std::vector<Ref<Texture3D>> textures;

        for (uint32_t i{0}; i < scene->mNumMeshes; ++i) {
            aiMesh* mesh = scene->mMeshes[i];
            for (uint32_t j{0}; j < mesh->mNumVertices; ++j) {
                aiVector3D pos = mesh->mVertices[j];

                // TODO: переделать способ получения цвета.
                // aiColor4D* color = mesh->mColors[j];

                Vertex3D vertex;
                vertex.Position = glm::vec3(pos.x, pos.y, pos.z);
                // if (color == nullptr) {
                //     EG_CORE_ERROR("null");
                //     EG_CORE_ASSERT(false);
                // }
                vertex.Color = glm::vec4(1.f/*color->r, color->g, color->b, color->a*/);

                vertices.push_back(vertex);
            }
            for (uint32_t j{0}; j < mesh->mNumFaces; ++j) {
                aiFace face = mesh->mFaces[j];
                for (uint32_t k{0}; k < face.mNumIndices; ++k) {
                    indeces.push_back(face.mIndices[k]);
                }
            }
        }

        return std::make_shared<Mesh>(vertices, indeces);
    }


}
