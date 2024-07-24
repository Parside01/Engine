#include "Engine/Scene/Scene.hpp"
#include "Engine/benchmark/Benchmark.hpp"
#include "Engine/Scene/Entity.hpp"


namespace Engine {
    Scene::Scene() {
    }

    Scene::~Scene() {
    }

    Entity Scene::CreateEntity() {
        return Entity(m_Registry.create(), this);
    }

    void Scene::OnUpdate(float tick) {
        EG_PROFILE_FUNC();
    }
}
