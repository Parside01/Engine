#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include "entt.hpp"

namespace Engine {

    class Scene {
    public:
        Scene();
        virtual ~Scene();

        void OnUpdate(float tick);
    private:
        entt::registry m_Registry;
    };

}

#endif //ENGINE_SCENE_HPP
