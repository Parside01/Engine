#include "Engine/Scene/Scene.hpp"

#include <Engine/Render/MeshManager.hpp>

#include "Engine/benchmark/Benchmark.hpp"
#include "Engine/log/Log.hpp"
#include "Engine/Scene/BaseComponents.hpp"
#include "Engine/Scene/TransfromComponent.hpp"
#include "Engine/Scene/CameraComponent.hpp"
#include "Engine/Scene/Entity.hpp"
#include "Engine/Render/Renderer2D.hpp"
#include "Engine/Scene/RenderableComponents.hpp"
#include "Engine/Scene/Systems/TransformSystem.hpp"

#include <Engine/Render/Renderer3D.hpp>

namespace Engine {
    Scene::Scene()
        :   mTrainMesh(MeshManager::CreateMesh("assets/models/Train.fbx")), mZombieMesh(MeshManager::CreateMesh("assets/models/Medium.fbx"))
            , mSkybox(std::make_shared<Skybox>("assets/textures/Skybox.png"))
    {
        mZombieTexture.Texture = TextureManager::CreateTexture("assets/textures/ZombieMale.png");
        mTrainTexture.Texture = TextureManager::CreateTexture("assets/textures/Temp.png");
    }

    Scene::~Scene() {}

    Entity Scene::CreateEntity(const std::string &name) {
        Entity entity(m_Registry.create(), this);
        entity.AddComponent<TagComponent>(name);
        entity.AddComponent<TransformComponent>();
        return entity;  
    }

    void Scene::RemoveEntity(Entity entity) {
        m_Registry.destroy(entity);
    }

    void Scene::OnUpdateRuntime(float tick) {
        const auto group = m_Registry.view<TagComponent, TransformComponent, CameraComponent>();
        SceneCamera* mainCamera = nullptr;
        glm::mat4 transform;
        for (const auto entity : group) {
            auto [tag, transformComponent, cameraComponent] = group.get<TagComponent, TransformComponent, CameraComponent>(entity);
            if (cameraComponent.IsPrimary) {
                mainCamera = &cameraComponent.Camera;
                TransformComponent ctc = transformComponent;
                transform = TransformSystem::CalculateTransform(ctc);
                break;
            }
        }
        if (!mainCamera) return;
    }

    void Scene::OnUpdateEditor(float tick, EditorCamera& camera) {
        EG_PROFILE_FUNC();

        mSkybox->Draw(std::make_shared<EditorCamera>(camera));
        Renderer3D::BeginScene(std::make_shared<EditorCamera>(camera));
        {
            TransformComponent tMale;
            tMale.Scale = glm::vec3(10.f);
            for (uint32_t x{0}; x < 2; ++x) {
                for (uint32_t y{0}; y < 2; ++y) {
                    tMale.Position.x += 80.f;
                    tMale.Rotation = glm::rotate(tMale.Rotation, glm::radians(-90.f), glm::vec3(1, 0, 0));
                    Renderer3D::DrawMesh(mZombieMesh, tMale, mZombieTexture);
                }
                tMale.Position.x = 0.f;
                tMale.Position.y += 80.f;
            }

            Renderer3D::DrawMesh(mTrainMesh, TransformComponent(), mTrainTexture);
        }
        Renderer3D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height) {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view) {
            CameraComponent& component = view.get<CameraComponent>(entity);
            if (!component.FixedAspectRatio) {
                component.Camera.SetViewportSize(width, height);
            }
        }
    }
}
