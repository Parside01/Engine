#include "Engine/Render/Renderer2D.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include "Engine/Render/Shader.hpp"
#include "Engine/Render/VertexArray.hpp"
#include "Engine/Render/Buffers.hpp"
#include "Engine/Render/RenderCommand.hpp"
#include "Engine/Render/OpenGL/Shader_OpenGL.hpp"

namespace Engine {

    struct Renderer2Data {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> QuadShader;
    };
    static Renderer2Data* s_Data;

    void Renderer2D::Init() {
        s_Data = new Renderer2Data;

        s_Data->QuadVertexArray = VertexArray::Create();
        float vertices[4 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };

        Engine::Ref<Engine::VertexBuffer> VB = VertexBuffer::Create(vertices, sizeof(vertices));
        VB->SetLayout({
            { "a_Position", ShaderDataType::Float3 },
        });
        s_Data->QuadVertexArray->AddVertexBuffer(VB);

        uint32_t indeces[6] = {0, 1, 2, 2, 3, 0};
        Ref<Engine::IndexBuffer> IB;
        IB = IndexBuffer::Create(indeces, sizeof(indeces) / sizeof(uint32_t));
        s_Data->QuadVertexArray->SetIndexBuffer(IB);

        s_Data->QuadShader = Shader::Create("assets/shaders/Layer2D.glsl");
    }

    void Renderer2D::Shutdown() {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthCamera &camera) {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->QuadShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->QuadShader)->SetUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->QuadShader)->SetUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene() {
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->QuadShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->QuadShader)->SetUniformFloat4("u_Color", color);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}
