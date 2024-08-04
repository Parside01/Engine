#include <Engine/benchmark/Benchmark.hpp>
#include <Engine/Render/RenderCommand.hpp>
#include <Engine/Render/Renderer3D.hpp>
#include <Engine/Render/Shader.hpp>
#include <Engine/Render/VertexArray.hpp>
#include <Engine/Render/Texture/TextureManager.hpp>
#include <Engine/Scene/Systems/TransformSystem.hpp>

namespace Engine {

    struct Renderer3Data {
        static constexpr uint32_t MaxVertices = std::pow(2, 14);
        static constexpr uint32_t MaxIndices = MaxVertices * 2;
        static constexpr uint32_t MaxTextureSlots = 32;

        uint32_t IndicesCount = 0;
        uint32_t IndicesOffset = 0;

        static Scope<uint32_t[]> RendererIndexBuffer;
        Ref<Shader> RendererShader;
        Ref<VertexArray> RendererVertexArray;
        Ref<VertexBuffer> RendererVertexBuffer;

        Vertex3D* VertexBufferBase = nullptr;
        Vertex3D* VertexBufferPtr = nullptr;

        Ref<Texture2D> WhiteTexture;

        Ref<Camera> RendererCamera;
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
                // { "a_TexCoord", ShaderDataType::Float2 },
                // { "a_TextureIndex", ShaderDataType::Float },
                { "a_EntityID", ShaderDataType::Int },
        });
        sData->RendererVertexArray->AddVertexBuffer(sData->RendererVertexBuffer);

        sData->VertexBufferBase = new Vertex3D[sData->MaxVertices];

        sData->RendererShader = Shader::Create("assets/shaders/Scene.glsl");
        sData->WhiteTexture = TextureManager::CreateTexture(128, 128, {1.f, 1.f, 1.f, 1.f});
    }

    void Renderer3D::Shutdown() {
    }

    void Renderer3D::BeginScene(const Ref<EditorCamera>& camera) {
        sData->RendererCamera = camera;

        sData->RendererShader->Bind();
        sData->RendererShader->SetMat4("u_ViewProjection", camera->GetViewProjection());

        StartBatch();
    }

    void Renderer3D::StartBatch() {
        EG_CORE_INFO("StartBatch");
        sData->IndicesCount = 0;
        sData->IndicesOffset = 0;

        sData->RendererIndexBuffer.reset(new uint32_t[sData->MaxIndices]);
        sData->VertexBufferPtr = sData->VertexBufferBase;
    }

    void Renderer3D::NextBatch() {
        Flush();
        StartBatch();
    }

    void Renderer3D::EndScene() {
        EG_PROFILE_FUNC();

        Flush();
    }

    void Renderer3D::Flush() {
        sData->RendererVertexArray->SetIndexBuffer(IndexBuffer::Create(sData->RendererIndexBuffer.get(), sData->MaxIndices));
        sData->RendererVertexBuffer->SetData(sData->VertexBufferBase, reinterpret_cast<uint8_t*>(sData->VertexBufferPtr) - reinterpret_cast<uint8_t*>(sData->VertexBufferBase));
        RenderCommand::DrawIndexed(sData->RendererVertexArray, sData->IndicesCount);
    }

    void Renderer3D::DrawMesh(const Ref<Mesh> &mesh, const TransformComponent &transform) {
        glm::mat4 t = TransformSystem::CalculateTransform(transform);
        for (const Vertex3D& vertex : mesh->GetVertices()) {
            sData->VertexBufferPtr->Position = t * glm::vec4(vertex.Position, 1.f);
            sData->VertexBufferPtr->Color = vertex.Color;
            sData->VertexBufferPtr++;
        }
        for (const uint32_t& indices : mesh->GetIndeces()) {
            sData->RendererIndexBuffer.get()[sData->IndicesCount] = indices;
            sData->IndicesCount++;
        }
    }
}
