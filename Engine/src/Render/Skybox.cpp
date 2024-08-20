#include <Engine/Render/Skybox.hpp>
#include <Engine/Render/Texture/TextureManager.hpp>

#include "Engine/Render/RenderCommand.hpp"

namespace Engine {
    Skybox::Skybox(const std::string &path) {
        mCubeMap = TextureManager::CreateCubeMap({
            "assets/textures/Skybox/posz.jpg",
            "assets/textures/Skybox/negz.jpg",
            "assets/textures/Skybox/posy.jpg",
            "assets/textures/Skybox/negy.jpg",
            "assets/textures/Skybox/posx.jpg",
            "assets/textures/Skybox/negx.jpg",
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

    void Skybox::Draw(const Ref<EditorCamera> &camera) {
        mVertexArray->Bind();

        mShader->Bind();

        float skyboxRadius = 500.f;
        // glm::vec3 direction = glm::normalize(-glm::vec3(camera->GetViewMatrix()[3]));
        // glm::mat4 viewMatrix = camera->GetViewMatrix() * glm::lookAt(glm::vec3(0.f), direction, glm::vec3(0, 1, 0));

        glm::mat4 modelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(skyboxRadius * 2));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f));

        glm::vec3 cameraPosition = camera->GetPosition();
        cameraPosition.x = glm::clamp(cameraPosition.x, -skyboxRadius, skyboxRadius);
        cameraPosition.y = glm::clamp(cameraPosition.y, -skyboxRadius, skyboxRadius);
        cameraPosition.z = glm::clamp(cameraPosition.z, -skyboxRadius, skyboxRadius);
        glm::mat4 viewMatrix = glm::lookAt(cameraPosition, /*glm::vec3(0.f)*/
                                           glm::normalize(glm::vec3(camera->GetViewMatrix()[3])), glm::vec3(0, 1, 0));

        mShader->SetMat4("u_View", viewMatrix);
        mShader->SetMat4("u_Model", modelMatrix);
        mShader->SetMat4("u_Projection", camera->GetProjectionMatrix());
        mShader->SetFloat("u_ClipDistance", 100.f);
        mShader->SetInt("u_Skybox", 0);
        mCubeMap->Bind();

        RenderCommand::DrawIndexed(mVertexArray, 36);

        mShader->Unbind();
        mVertexArray->Unbind();
    }
}
