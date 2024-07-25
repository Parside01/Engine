#include "Engine/Scene/Entity.hpp"
#include "Engine/engine_precompile_headers.hpp"

namespace Engine {

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {

    }
}
