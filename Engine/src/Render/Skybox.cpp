#include <Engine/Render/Skybox.hpp>
#include <Engine/Render/Texture/TextureManager.hpp>

#include "Engine/Render/RenderCommand.hpp"

namespace Engine {
    Skybox::Skybox(const std::string &path) {
        mCubeMap = TextureManager::CreateCubeMap({
            "assets/textures/Skybox/posx.jpg",
            "assets/textures/Skybox/negx.jpg",
            "assets/textures/Skybox/posy.jpg",
            "assets/textures/Skybox/negy.jpg",
            "assets/textures/Skybox/posz.jpg",
            "assets/textures/Skybox/negz.jpg"
        });
        mShader = Shader::Create("assets/shaders/Skybox.glsl");
        mVertexArray = VertexArray::Create();

        float vertices[24] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
        };
        Ref<VertexBuffer> vb = VertexBuffer::Create(vertices, sizeof(vertices));
        vb->SetLayout({
            {"a_Position", ShaderDataType::Float3},
        });
        mVertexArray->AddVertexBuffer(vb);

        uint32_t indices[36] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            0, 4, 5, 5, 1, 0,
            1, 5, 6, 6, 2, 1,
            2, 6, 7, 7, 3, 2,
            3, 7, 4, 4, 0, 3,
        };
        Ref<IndexBuffer> ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        mVertexArray->SetIndexBuffer(ib);
    }

    void Skybox::Draw(const Ref<EditorCamera>& camera) {
        mVertexArray->Bind();

        mShader->Bind();
        mShader->SetMat4("u_View", glm::mat4(glm::mat3(camera->GetViewMatrix())));
        mShader->SetMat4("u_Projection", camera->GetProjectionMatrix());
        mShader->SetInt("u_Skybox", 0);
        mCubeMap->Bind();

        RenderCommand::DrawIndexed(mVertexArray, 36);

        mShader->Unbind();
        mVertexArray->Unbind();
    }
}
