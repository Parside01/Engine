#include "Engine/Scene/Entity.hpp"
#include "Engine/engine_precompile_headers.hpp"

namespace Engine {

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {

    }

    template<typename T, typename... Args>
    T& Entity::AddComponent(Args &&...args) {
        return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
    }

    template<typename T>
    T& Entity::GetComponent() {
       return m_Scene->m_Registry.get<T>(m_EntityHandle);
    }

    template<typename T>
    void Entity::RemoveCompoent() {
        m_Scene->m_Registry.remove<T>(m_EntityHandle);
    }

    template<typename... Type>
    bool Entity::HasComponent() const {
        return m_Scene->m_Registry.all_of<Type...>(m_EntityHandle);
    }

    Entity::operator bool() const {
        return m_EntityHandle != entt::null;
    }

}
