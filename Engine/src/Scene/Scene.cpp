#include "Engine/Scene/Scene.hpp"
#include "Engine/benchmark/Benchmark.hpp"
#include "Engine/Scene/BaseComponents.hpp"
#include "Engine/Scene/TransfromComponent.hpp"
#include "Engine/Scene/CameraComponent.hpp"
#include "Engine/Scene/Entity.hpp"


namespace Engine {
    Scene::Scene() {
    }

    Scene::~Scene() {
    }

    Entity Scene::CreateEntity(const std::string &name) {
        Entity entity(m_Registry.create(), this);
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name;
        entity.AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::OnUpdate(float tick) {
        EG_PROFILE_FUNC();

        const auto group = m_Registry.view<TransformComponent, CameraComponent>();
        glm::mat4* cameraTranform = nullptr;
        for (const auto entity : group) {
            auto [transformComponent, cameraComponent] = group.get<TransformComponent, CameraComponent>(entity);

        }
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height) {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view) {
            CameraComponent& component = view.get<CameraComponent>(entity);
            if (!component.FixedAspectRation) {
                component.Camera.SetViewportSize(width, height);
            }
        }
    }
}
