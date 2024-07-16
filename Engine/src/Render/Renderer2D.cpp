#include "Engine/Render/Renderer2D.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include "Engine/Render/Shader.hpp"
#include "Engine/Render/VertexArray.hpp"
#include "Engine/Render/Buffers.hpp"
#include "Engine/Render/RenderCommand.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

    struct Renderer2Data {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> QuadShader;
        Ref<Shader> TextureShader;
    };
    static Renderer2Data* s_Data;

    void Renderer2D::Init() {
        s_Data = new Renderer2Data;

        s_Data->QuadVertexArray = VertexArray::Create();
        float vertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 
        };

        Engine::Ref<Engine::VertexBuffer> VB = VertexBuffer::Create(vertices, sizeof(vertices));
        VB->SetLayout({
            { "a_Position", ShaderDataType::Float3 },
            { "a_TexCoord", ShaderDataType::Float2 },
        });
        s_Data->QuadVertexArray->AddVertexBuffer(VB);

        uint32_t indeces[6] = {0, 1, 2, 2, 3, 0};
        Ref<Engine::IndexBuffer> IB;
        IB = IndexBuffer::Create(indeces, sizeof(indeces) / sizeof(uint32_t));
        s_Data->QuadVertexArray->SetIndexBuffer(IB);

        s_Data->QuadShader = Shader::Create("assets/shaders/Layer2D.glsl");

        s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown() {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthCamera &camera) {
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        s_Data->QuadShader->Bind();
        s_Data->QuadShader->SetFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.f});
        s_Data->QuadShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
        DrawQuad({position.x, position.y, 0}, size, texture);
    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
        s_Data->TextureShader->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.f});
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        texture->Bind(0);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}

