#include "Engine/Scene/Scene.hpp"

#include "Engine/benchmark/Benchmark.hpp"
#include "Engine/log/Log.hpp"
#include "Engine/Scene/BaseComponents.hpp"
#include "Engine/Scene/TransfromComponent.hpp"
#include "Engine/Scene/CameraComponent.hpp"
#include "Engine/Scene/Entity.hpp"
#include "Engine/Render/Renderer2D.hpp"
#include "Engine/Scene/RenderableComponents.hpp"
#include "Engine/Scene/Systems/TransformSystem.hpp"

namespace Engine {
    Scene::Scene() {}

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

    void Scene::OnUpdate(float tick) {
        EG_PROFILE_FUNC();

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

        Renderer2D::BeginScene(*mainCamera, transform);
        {   
            const auto group = m_Registry.group<TagComponent, TransformComponent>(entt::get<SpriteComponent>);
            for (auto entity : group) {
                auto [tag, transformComponent, sprite] = group.get<TagComponent, TransformComponent, SpriteComponent>(entity);
                Renderer2D::DrawQuad(transformComponent.Position, {transformComponent.Scale.x, transformComponent.Scale.y}, transformComponent.Rotation, sprite.Color);
            }
        }
        Renderer2D::EndScene();

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
