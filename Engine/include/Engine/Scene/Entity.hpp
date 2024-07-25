#ifndef ENGINE_ENTITY_HPP
#define ENGINE_ENTITY_HPP

#include "Engine/Scene/Scene.hpp"
#include "Engine/Core.hpp"
#include "entt.hpp"

namespace Engine {

    class Entity {
    public:

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

    private:
        entt::entity m_EntityHandle{entt::null};
        Scene* m_Scene{nullptr};
    };

}

#endif //ENGINE_ENTITY_HPP
