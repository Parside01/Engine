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
        T& AddComponent(Args &&...args);

        template<typename T>
        T& GetComponent();

        template<typename T>
        void RemoveCompoent();

        template<typename... Type>
        [[nodiscard]] bool HasComponent() const;

        operator bool() const;
    private:
        entt::entity m_EntityHandle{ entt::null };
        Scene* m_Scene{nullptr};
    };

}

#endif //ENGINE_ENTITY_HPP
