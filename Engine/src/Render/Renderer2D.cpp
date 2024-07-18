#include "Engine/Render/Renderer2D.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include "Engine/Render/Shader.hpp"
#include "Engine/Render/VertexArray.hpp"
#include "Engine/Render/Buffers.hpp"
#include "Engine/Render/RenderCommand.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

    struct QuadVertex {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
    };

    struct Renderer2Data {
        const uint32_t MaxQuads = 100000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> QuadShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
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

        s_Data->QuadShader = Shader::Create("assets/shaders/Layer2D.glsl");

        s_Data->QuadShader->Bind(); 
        s_Data->QuadShader->SetInt("u_Texture", 0);

        s_Data->WhiteTexture = Texture2D::Create(1, 1);
    }

    void Renderer2D::Shutdown() {
        EG_PROFILE_FUNC();
        delete s_Data;
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

    void Renderer2D::Flush() {
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray, s_Data->QuadIndexCount);
    }
 
    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        EG_PROFILE_FUNC();

        s_Data->QuadVertexBufferPtr->Position = position;
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = {position.x + size.x, position.y, 0.0f};
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = {position.x + size.x, position.y + size.y, 0.0f};
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadVertexBufferPtr->Position = {position.x, position.y + size.y, 0.0f};
        s_Data->QuadVertexBufferPtr->Color = color;
        s_Data->QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
        s_Data->QuadVertexBufferPtr++;

        s_Data->QuadIndexCount += 6;

        /* s_Data->QuadShader->SetFloat("u_TextureScale", 1.0f);
        s_Data->WhiteTexture->Bind(0);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.f});
        s_Data->QuadShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray); */
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale) {
        DrawQuad({position.x, position.y, 0}, size, texture);
    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float textureScale) {
        EG_PROFILE_FUNC();
        s_Data->QuadShader->SetFloat4("u_Color", glm::vec4(1.0f));        
        s_Data->QuadShader->SetFloat("u_TextureScale", textureScale);
        texture->Bind(0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.f});
        s_Data->QuadShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}

