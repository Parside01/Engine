#include <Engine/benchmark/Benchmark.hpp>
#include <Engine/Render/RenderCommand.hpp>
#include <Engine/Render/Renderer3D.hpp>
#include <Engine/Render/Shader.hpp>
#include <Engine/Render/VertexArray.hpp>
#include <Engine/Render/Texture/TextureManager.hpp>
#include <Engine/Scene/Systems/TransformSystem.hpp>

#include "Engine/Render/UniformBuffer.hpp"
#include "Engine/Scene/RenderableComponents.hpp"


// TODO: пока все эксперементально, дальше нужно переписать и сделать оптимизацию.
namespace Engine {
    struct Renderer3Data {
        static constexpr uint32_t MaxVertices = 4194304;
        static constexpr uint32_t MaxIndices = 8388608;
        static constexpr uint32_t MaxTextureSlots = 32;

        uint32_t IndicesCount = 0;
        uint32_t VerticesCount = 0;
        uint32_t IndicesOffset = 0;

        static Scope<uint32_t[]> RendererIndexBuffer;
        Ref<Shader> RendererShader;
        Ref<VertexArray> RendererVertexArray;
        Ref<VertexBuffer> RendererVertexBuffer;

        Vertex3D *VertexBufferBase = nullptr;
        Vertex3D *VertexBufferPtr = nullptr;

        Ref<Texture2D> WhiteTexture;

        Ref<EditorCamera> RendererCamera;

        std::vector<Mesh::NestedMesh> NestedMeshes;

        struct CameraData {
            glm::mat4 View;
            glm::mat4 Projection;
        } CameraData; // binding = 0.
        Ref<UniformBuffer> CameraDataBuffer;

        struct LightData {
            glm::vec3 LightColor;
            glm::vec3 LightPosition;
        } LightData; // binding = 1.
        Ref<UniformBuffer> LightDataBuffer;

        struct TextureData {
            int Texture;
        } TextureData; // binding = 2.
        Ref<UniformBuffer> TextureDataBuffer;
    };

    static Scope<Renderer3Data> sData = std::make_unique<Renderer3Data>();
    Scope<uint32_t[]> Renderer3Data::RendererIndexBuffer = std::make_unique<uint32_t[]>(sData->MaxIndices);

    void Renderer3D::Init() {
        EG_PROFILE_FUNC();

        sData->RendererVertexArray = VertexArray::Create();

        sData->RendererVertexBuffer = VertexBuffer::Create(sizeof(Vertex3D) * sData->MaxVertices);
        sData->RendererVertexBuffer->SetLayout({
            {"a_Position", ShaderDataType::Float3},
            {"a_Color", ShaderDataType::Float4},
            {"a_TexCoord", ShaderDataType::Float2},
            {"a_Normal", ShaderDataType::Float3},
            // { "a_TextureIndex", ShaderDataType::Float },
            {"a_EntityID", ShaderDataType::Int},
        });
        sData->RendererVertexArray->AddVertexBuffer(sData->RendererVertexBuffer);

        sData->VertexBufferBase = new Vertex3D[sData->MaxVertices];

        sData->RendererShader = Shader::Create("assets/shaders/Scene.glsl");
        // sData->WhiteTexture = TextureManager::CreateTexture(128, 128, {1.f, 1.f, 1.f, 1.f});

        sData->CameraDataBuffer = UniformBuffer::Create(sizeof(Renderer3Data::CameraData), 0);
        sData->LightDataBuffer = UniformBuffer::Create(sizeof(Renderer3Data::LightData), 1);
        sData->TextureDataBuffer = UniformBuffer::Create(sizeof(Renderer3Data::TextureData), 2);
    }

    void Renderer3D::Shutdown() {
        delete[] sData->VertexBufferBase;
        sData->VertexBufferBase = nullptr;
    }

    void Renderer3D::BeginScene(const Ref<EditorCamera> &camera) {
        EG_PROFILE_FUNC();
        sData->RendererCamera = camera;

        sData->CameraData.Projection = camera->GetProjectionMatrix();
        sData->CameraData.View = camera->GetViewMatrix();
        sData->CameraDataBuffer->SetData(&sData->CameraData, sizeof(Renderer3Data::CameraData));

        sData->LightData.LightColor = glm::vec3(0.95f);
        sData->LightData.LightPosition = glm::vec3(100.f, 150.f, 50.f);
        sData->LightDataBuffer->SetData(&sData->LightData, sizeof(Renderer3Data::LightData));

        sData->TextureData.Texture = 1;
        sData->TextureDataBuffer->SetData(&sData->TextureData, sizeof(Renderer3Data::TextureData));


        sData->RendererShader->Bind();
        sData->RendererShader->SetInt("u_Texture", 1);

        // sData->RendererShader->SetMat4("u_View", camera->GetViewMatrix());
        // sData->RendererShader->SetMat4("u_Projection", camera->GetProjectionMatrix());
        //
        //
        // // TODO: нужно как-то по другому это делать.
        // sData->RendererShader->SetFloat3("u_LightColor", glm::vec3(0.95f, 0.95f, 0.95f));
        // sData->RendererShader->SetFloat3("u_LightPosition", glm::vec3(100.f, 150.f, 50.f));

        StartBatch();
    }

    void Renderer3D::StartBatch() {
        EG_PROFILE_FUNC();
        sData->IndicesCount = 0;
        sData->IndicesOffset = 0;
        sData->VerticesCount = 0;

        sData->RendererIndexBuffer.reset(new uint32_t[sData->MaxIndices]);
        sData->VertexBufferPtr = sData->VertexBufferBase;

        sData->NestedMeshes.clear();
    }

    void Renderer3D::EndScene() {
        EG_PROFILE_FUNC();

        Flush();
    }

    void Renderer3D::NextBatch() {
        EG_PROFILE_FUNC();
        Flush();
        StartBatch();
    }

    void Renderer3D::Flush() {
        EG_PROFILE_FUNC(); {
            EG_PROFILE_SCOPE("Выделение памяти и тд");
            sData->RendererVertexArray->SetIndexBuffer(
                IndexBuffer::Create(sData->RendererIndexBuffer.get(), sData->IndicesCount));
            size_t dataSize = (sData->VertexBufferPtr - sData->VertexBufferBase) * sizeof(Vertex3D);
            sData->RendererVertexBuffer->SetData(sData->VertexBufferBase, dataSize);
        }

        TextureManager::BindTextures();
        for (int i = 0; i < sData->NestedMeshes.size(); ++i) {
            RenderCommand::DrawIndexedBaseVertex(sData->RendererVertexArray, sData->NestedMeshes[i].mNumIndices,
                                                 sData->NestedMeshes[i].mBaseIndex, sData->NestedMeshes[i].mBaseVertex);
        }
    }

    void Renderer3D::DrawMesh(const Ref<Mesh> &mesh, const TransformComponent &transform,
                              const SpriteComponent &sprite) {
        EG_PROFILE_FUNC();
        glm::mat4 t = TransformSystem::CalculateTransform(transform);
        for (auto &n: mesh->GetNestedMeshes()) {
            sData->NestedMeshes.push_back(n);
        }

        std::array<glm::vec2, 4> coords = TextureManager::GetTextureCoords(sprite.Texture);
        for (const Vertex3D &vertex: mesh->GetVertices()) {
            sData->VertexBufferPtr->Position = t * glm::vec4(vertex.Position, 1.f);

            glm::vec2 textureCoord = vertex.TextureCoord;
            textureCoord.x = coords[0].x + (coords[1].x - coords[0].x) * textureCoord.x;
            textureCoord.y = coords[0].y + (coords[2].y - coords[0].y) * (1 - textureCoord.y);

            sData->VertexBufferPtr->TextureCoord = textureCoord;
            sData->VertexBufferPtr->Normal = vertex.Normal;
            // sData->VertexBufferPtr->TextureIndex = 1;
            sData->VertexBufferPtr->Color = glm::vec4(1.f);

            sData->VertexBufferPtr++;
            sData->VerticesCount++;
        }
        for (const uint32_t &index: mesh->GetIndices()) {
            sData->RendererIndexBuffer.get()[sData->IndicesCount] = index;
            sData->IndicesCount++;
        }
        NextBatch();
    }
}
