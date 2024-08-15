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
        :mPoliceMesh(MeshManager::CreateMesh("assets/models/police.fbx")), mMaleMesh(MeshManager::CreateMesh("assets/models/Male.fbx"))
    {}

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
        Renderer3D::BeginScene(std::make_shared<EditorCamera>(camera));
        {
            TransformComponent tMale;
            tMale.Scale = glm::vec3(0.2f);
            for (uint32_t x{0}; x < 10; ++x) {
                for (uint32_t y{0}; y < 10; ++y) {
                    tMale.Position.x += 20.f;
                    Renderer3D::DrawMesh(mMaleMesh, tMale);
                }
                tMale.Position.x = 0.f;
                tMale.Position.y += 20.f;
            }

            TransformComponent tPolice;
            tPolice.Position.x -= 150.f;
            Renderer3D::DrawMesh(mPoliceMesh, tPolice);
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
