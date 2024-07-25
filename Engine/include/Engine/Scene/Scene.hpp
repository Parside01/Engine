#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include "entt.hpp"


namespace Engine {
    class Entity;

    class Scene {
        friend class Entity;
    public:
        Scene();
        virtual ~Scene();

        Entity CreateEntity(const std::string &name = "No name entity");

        void OnUpdate(float tick);
        void OnViewportResize(uint32_t width, uint32_t height);
    private:

        uint32_t m_ViewportWidth{0};
        uint32_t m_ViewportHeight{0};

        entt::registry m_Registry;
    };

}

#endif //ENGINE_SCENE_HPP
