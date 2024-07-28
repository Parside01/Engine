#ifndef ENGINE_ENTITY_HPP
#define ENGINE_ENTITY_HPP

#include "Engine/Scene/Scene.hpp"
#include "Engine/Core.hpp"
#include "entt.hpp"

namespace Engine {

    class Entity {
    public:
        Entity() {};
        Entity(entt::entity handle, Scene* scene);

        template<class T, class ... Args>
        T& AddComponent(Args &&...args) {
            return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() {
            return m_Scene->m_Registry.get<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveCompoent() {
            m_Scene->m_Registry.remove<T>(m_EntityHandle);
        }

        template<typename... Type>
        [[nodiscard]] bool HasComponent() const {
            return m_Scene->m_Registry.all_of<Type...>(m_EntityHandle);
        }

        operator bool() const {
            return m_EntityHandle != entt::null;
        }

        operator uint32_t() const {
            return static_cast<uint32_t>(m_EntityHandle);
        }

        bool operator==(Entity other) const {
            return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
        }

        bool operator!=(Entity other) const {
            return !(*this == other);
        }

        operator entt::entity() { return m_EntityHandle; }

    private:
        entt::entity m_EntityHandle{entt::null};
        Scene* m_Scene{nullptr};
    };

}

#endif //ENGINE_ENTITY_HPP
