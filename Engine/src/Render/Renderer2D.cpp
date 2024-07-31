#include "Engine/Render/Renderer2D.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include "Engine/Render/Shader.hpp"
#include "Engine/Render/VertexArray.hpp"
#include "Engine/Render/Buffers.hpp"
#include "Engine/Render/RenderCommand.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Engine {

    struct QuadVertex {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TextureIndex;

        int EntityID = 1;
    };

    struct Renderer2Data {
        static constexpr uint32_t MaxQuads{100000};
        static constexpr uint32_t MaxVertices = MaxQuads * 4;
        static constexpr uint32_t MaxIndices = MaxQuads * 6;
        static constexpr uint32_t MaxTextureSlots{32};

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> QuadShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount{0};
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        uint32_t TextureSlotIndex{1}; // Нулевой слот занят стандартной белой текстурой.
        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;

        glm::vec4 QuadVertexPosition[4];

        struct CameraData {
            glm::mat4 ViewProjection;
        };
        CameraData CameraBuffer;
        // Ref<UniformBuffer> CameraUniformBuffer;
    };

    static Renderer2Data* s_Data;

    void Renderer2D::Init() {
        EG_PROFILE_FUNC();

        s_Data = new Renderer2Data;

        s_Data->QuadVertexArray = VertexArray::Create();

        s_Data->QuadVertexBuffer = VertexBuffer::Create(s_Data->MaxVertices * sizeof(QuadVertex));
        s_Data->QuadVertexBuffer->SetLayout({
            { "a_Position", ShaderDataType::Float3 },
            { "a_Color",    ShaderDataType::Float4 },
            { "a_TexCoord", ShaderDataType::Float2 },
            { "a_TextureIndex", ShaderDataType::Float },
            { "a_EntityID", ShaderDataType::Int },
        });
        s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);

        s_Data->QuadVertexBufferBase = new QuadVertex[s_Data->MaxVertices];

        uint32_t* indeces = new uint32_t[s_Data->MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i{0}; i < s_Data->MaxIndices; i += 6) {
            indeces[i + 0] = offset + 0;
            indeces[i + 1] = offset + 1;
            indeces[i + 2] = offset + 2;

            indeces[i + 3] = offset + 2;
            indeces[i + 4] = offset + 3;
            indeces[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<Engine::IndexBuffer> IB;
        IB = IndexBuffer::Create(indeces, s_Data->MaxIndices);
        s_Data->QuadVertexArray->SetIndexBuffer(IB);

        delete[] indeces;

        int32_t samplers[s_Data->MaxTextureSlots];
        for (uint32_t i{0}; i < s_Data->MaxTextureSlots; ++i) samplers[i] = i;

        s_Data->QuadShader = Shader::Create("../assets/shaders/Layer2D.glsl");

        s_Data->QuadShader->Bind();
        s_Data->WhiteTexture = Texture2D::Create(1, 1);
        s_Data->QuadShader->SetIntArray("u_Textures", samplers, s_Data->MaxTextureSlots);

        s_Data->TextureSlots[0] = s_Data->WhiteTexture;

        s_Data->QuadVertexPosition[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_Data->QuadVertexPosition[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_Data->QuadVertexPosition[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        s_Data->QuadVertexPosition[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

    }

    void Renderer2D::Shutdown() {
        EG_PROFILE_FUNC();
        delete s_Data;
    }

    void Renderer2D::BeginScene(const Camera &camera, const glm::mat4& transform) {
        EG_PROFILE_FUNC();

        glm::mat4 viewProjection = camera.GetProjection() * glm::inverse(transform);

        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", viewProjection);

        s_Data->QuadIndexCount = 0;
        s_Data->QuadVertexBufferPtr = s_Data->QuadVertexBufferBase;
    }

    void Renderer2D::BeginScene(const EditorCamera& camera) {
        EG_PROFILE_FUNC();
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjection());

        s_Data->QuadIndexCount = 0;
        s_Data->QuadVertexBufferPtr = s_Data->QuadVertexBufferBase;
    }

    void Renderer2D::BeginScene(const OrthCamera &camera) {
        EG_PROFILE_FUNC();
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data->QuadIndexCount = 0;
        s_Data->QuadVertexBufferPtr = s_Data->QuadVertexBufferBase;
    }

    void Renderer2D::EndScene() {
        EG_PROFILE_FUNC();

        s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexBufferBase, reinterpret_cast<uint8_t*>(s_Data->QuadVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data->QuadVertexBufferBase));
        Flush();
    }

    void Renderer2D::FlushAndReset() {
        EndScene();
        s_Data->QuadIndexCount = 0;
        s_Data->QuadVertexBufferPtr = s_Data->QuadVertexBufferBase;
    }

    void Renderer2D::Flush() {
        for (uint32_t i{0}; i < s_Data->TextureSlotIndex; ++i) {
            s_Data->TextureSlots[i]->Bind(i);
        }
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray, s_Data->QuadIndexCount);
    }

 
    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad(position, size, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), color, -1);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::quat& rotation, const glm::vec4& color, int entityID) {
        EG_PROFILE_FUNC();

        if (s_Data->QuadIndexCount >= s_Data->MaxIndices)
            FlushAndReset();

        constexpr float textureIndex{0.0f};

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[0];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr->EntityID = static_cast<int>(entityID);
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[1];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr->EntityID = static_cast<int>(entityID);
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[2];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr->EntityID = static_cast<int>(entityID);
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[3];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr->EntityID = static_cast<int>(entityID);
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadIndexCount += 6;   
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale) {
        DrawQuad({position.x, position.y, 0}, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale) {
        EG_PROFILE_FUNC();

        if (s_Data->QuadIndexCount >= s_Data->MaxIndices)
            FlushAndReset();

        constexpr glm::vec4 color(1.0f);

        float textureIndex{0.0f};
        for (uint32_t i{1}; i < s_Data->TextureSlotIndex; ++i) {
            if (*s_Data->TextureSlots[i].get() == *texture.get()) {
                textureIndex = i;
                break;
            }
        }
        if (textureIndex == 0.0f) {
            std::cout << textureIndex << std::endl;
            textureIndex = static_cast<uint32_t>(s_Data->TextureSlotIndex);
            s_Data->TextureSlots[s_Data->TextureSlotIndex] = texture;
            ++s_Data->TextureSlotIndex;
        }
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[0];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[1];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[2];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = transform * s_Data->QuadVertexPosition[3];
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
        s_Data->QuadVertexBufferPtr->TextureIndex = textureIndex;
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadIndexCount += 6;
    }
}

