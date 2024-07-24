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

        Entity CreateEntity();

        void OnUpdate(float tick);
    private:
        entt::registry m_Registry;
    };

}

#endif //ENGINE_SCENE_HPP
