#include <Engine/Render/MeshManager.hpp>
#include <Engine/log/Log.hpp>

namespace Engine {

    Ref<Mesh> MeshManager::CreateMesh(const std::string &path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            EG_CORE_ERROR("Не удалось загузить модель из файла {0}", path);
            EG_CORE_ASSERT(false);
            return nullptr;
        }

        Ref<Mesh> mesh = std::make_shared<Mesh>();
        InitMesh(scene, mesh);
        return mesh;
    }

    void MeshManager::InitMesh(const aiScene *scene, Ref<Mesh> &mesh) {
        mesh->mNestedMeshes.reserve(scene->mNumMeshes);

        CountVerticesAndMeshes(scene, mesh);
        ReserveMeshSpace(scene, mesh);
        InitAllNestedMeshes(scene, mesh);
    }

    void MeshManager::CountVerticesAndMeshes(const aiScene *scene, Ref<Mesh> &mesh) {
        for (uint32_t i{0}; i < scene->mNumMeshes; ++i) {
            Mesh::NestedMesh n;
            n.mMaterialIndex = scene->mMeshes[i]->mMaterialIndex;
            n.mNumIndices = scene->mMeshes[i]->mNumFaces * 3;
            n.mNumVertices = scene->mMeshes[i]->mNumVertices;
            n.mBaseVertex = mesh->mNumVertices;
            n.mBaseIndex = mesh->mNumIndices;
            mesh->mNestedMeshes.push_back(n);

            mesh->mNumVertices += mesh->mNestedMeshes[i].mNumVertices;
            mesh->mNumIndices += mesh->mNestedMeshes[i].mNumIndices;
        }
    }

    void MeshManager::ReserveMeshSpace(const aiScene *scene, Ref<Mesh> &mesh) {
        mesh->mIndices.reserve(mesh->mNumIndices);
        mesh->mVertices.reserve(mesh->mNumVertices);
    }

    void MeshManager::InitAllNestedMeshes(const aiScene *scene, Ref<Mesh> &mesh) {
        for (uint32_t i{0}; i < mesh->mNestedMeshes.size(); ++i) {
            InitNestedMesh(scene->mMeshes[i], mesh);
        }
    }

    void MeshManager::InitNestedMesh(const aiMesh *nested, Ref<Mesh> &mesh) {
        const aiVector3D zeroVector(0.f);
        for (uint32_t i{0}; i < nested->mNumVertices; ++i) {
            auto& pos = nested->mVertices[i];
            auto& texCoord = nested->HasTextureCoords(0) ? nested->mTextureCoords[0][i] : zeroVector;
            auto& normal = nested->mNormals[i];
            Vertex3D vertex;
            vertex.Position = glm::vec3(pos.x, pos.y, pos.z);
            vertex.TextureCoord = glm::vec2(texCoord.x, texCoord.y);
            vertex.Normal = glm::vec3(normal.x, normal.y, normal.z);

            mesh->mVertices.push_back(vertex);
        }

        for (uint32_t i{0}; i < nested->mNumFaces; ++i) {
            const auto& face = nested->mFaces[i];
            EG_CORE_ASSERT(face.mNumIndices == 3);

            mesh->mIndices.push_back(face.mIndices[0]);
            mesh->mIndices.push_back(face.mIndices[1]);
            mesh->mIndices.push_back(face.mIndices[2]);
        }
    }
}
