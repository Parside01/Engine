#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include "entt.hpp"
#include "Engine/Scene/EditorCamera.hpp"

#include "Engine/Render/Texture.hpp"

namespace Engine {

    class Entity;
    class Camera;

    class Scene {
        friend class Entity;
    public:
        Scene();
        virtual ~Scene();

        // Default components: TagComponent, TransformComponent.
        Entity CreateEntity(const std::string &name = "No name entity");
        void RemoveEntity(Entity entity);

        void OnUpdateRuntime(float tick);
        void OnUpdateEditor(float tick, EditorCamera& camera);
        void OnViewportResize(uint32_t width, uint32_t height);

        entt::registry& GetRegistry() { return m_Registry; }
    private:

        uint32_t m_ViewportWidth{0};
        uint32_t m_ViewportHeight{0};

        entt::registry m_Registry;
    };

}

#endif //ENGINE_SCENE_HPP
