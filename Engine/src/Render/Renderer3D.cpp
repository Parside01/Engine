#include <Engine/benchmark/Benchmark.hpp>
#include <Engine/Render/RenderCommand.hpp>
#include <Engine/Render/Renderer3D.hpp>
#include <Engine/Render/Shader.hpp>
#include <Engine/Render/VertexArray.hpp>
#include <Engine/Render/Texture/TextureManager.hpp>
#include <Engine/Scene/Systems/TransformSystem.hpp>


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

        Vertex3D* VertexBufferBase = nullptr;
        Vertex3D* VertexBufferPtr = nullptr;

        Ref<Texture2D> WhiteTexture;

        Ref<EditorCamera> RendererCamera;

        std::vector<Mesh::NestedMesh> NestedMeshes;
    };

    static Scope<Renderer3Data> sData = std::make_unique<Renderer3Data>();
    Scope<uint32_t[]> Renderer3Data::RendererIndexBuffer = std::make_unique<uint32_t[]>(sData->MaxIndices);

    void Renderer3D::Init() {
        EG_PROFILE_FUNC();

        sData->RendererVertexArray = VertexArray::Create();

        sData->RendererVertexBuffer = VertexBuffer::Create(sizeof(Vertex3D) * sData->MaxVertices);
        sData->RendererVertexBuffer->SetLayout({
                { "a_Position", ShaderDataType::Float3 },
                { "a_Color",    ShaderDataType::Float4 },
                { "a_TexCoord", ShaderDataType::Float2 },
                { "a_Normal",   ShaderDataType::Float3 },
                // { "a_TextureIndex", ShaderDataType::Float },
                { "a_EntityID", ShaderDataType::Int },
        });
        sData->RendererVertexArray->AddVertexBuffer(sData->RendererVertexBuffer);

        sData->VertexBufferBase = new Vertex3D[sData->MaxVertices];

        sData->RendererShader = Shader::Create("assets/shaders/Scene.glsl");
        sData->WhiteTexture = TextureManager::CreateTexture(128, 128, {1.f, 1.f, 1.f, 1.f});
    }

    void Renderer3D::Shutdown() {
        delete[] sData->VertexBufferBase;
        sData->VertexBufferBase = nullptr;
    }

    void Renderer3D::BeginScene(const Ref<EditorCamera>& camera) {
        EG_PROFILE_FUNC();
        sData->RendererCamera = camera;

        sData->RendererShader->Bind();
        sData->RendererShader->SetMat4("u_ViewProjection", camera->GetViewProjection());

        // TODO: нужно как-то по другому это делать.
        sData->RendererShader->SetFloat4("u_LightColor", glm::vec4(0.95f, 0.85f, 0.75f, 1.0f));
        sData->RendererShader->SetFloat3("u_LightPosition", glm::vec3(15.f));

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
        EG_PROFILE_FUNC();
        {
            EG_PROFILE_SCOPE("Выделение памяти и тд");
            sData->RendererVertexArray->SetIndexBuffer(IndexBuffer::Create(sData->RendererIndexBuffer.get(), sData->IndicesCount));
            size_t dataSize = (sData->VertexBufferPtr - sData->VertexBufferBase) * sizeof(Vertex3D);
            sData->RendererVertexBuffer->SetData(sData->VertexBufferBase, dataSize);
        }

        for (int i = 0; i < sData->NestedMeshes.size(); ++i) {
            RenderCommand::DrawIndexedBaseVertex(sData->RendererVertexArray, sData->NestedMeshes[i].mNumIndices, sData->NestedMeshes[i].mBaseIndex, sData->NestedMeshes[i].mBaseVertex);
        }
    }

    glm::vec3 LightColor = glm::vec3(1.f, 1.f, 1.0f);
    glm::vec3 LightPosition = glm::vec3(100.f, 150.f, 50.f);

    void Renderer3D::DrawMesh(const Ref<Mesh> &mesh, const TransformComponent &transform) {
        EG_PROFILE_FUNC();
        glm::mat4 t = TransformSystem::CalculateTransform(transform);
        for (auto& n : mesh->GetNestedMeshes()) {
            sData->NestedMeshes.push_back(n);
        }

        for (const Vertex3D& vertex : mesh->GetVertices()) {
            sData->VertexBufferPtr->Position = t * glm::vec4(vertex.Position, 1.f);
            sData->VertexBufferPtr->TextureCoord = vertex.TextureCoord;
            sData->VertexBufferPtr->Normal = vertex.Normal;

            glm::vec3 lightDir = glm::normalize(LightPosition - vertex.Position);
            glm::vec3 normal = glm::normalize(vertex.Normal);
            float dot = glm::dot(lightDir, normal);
            float lightValue = std::max(dot, 0.15f);

            sData->VertexBufferPtr->Color = glm::vec4(glm::vec3(1.f) * lightValue * LightColor, 1.f);

            sData->VertexBufferPtr++;
            sData->VerticesCount++;
        }
        for (const uint32_t& index : mesh->GetIndices()) {
            sData->RendererIndexBuffer.get()[sData->IndicesCount] = index;
            sData->IndicesCount++;
        }
        NextBatch();
    }
}