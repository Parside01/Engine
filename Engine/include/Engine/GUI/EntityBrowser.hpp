#ifndef ENGINE_ENTITY_BROWSER_HPP
#define ENGINE_ENTITY_BROWSER_HPP


#include "Engine/Scene/Scene.hpp"
#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Scene/Entity.hpp"


namespace Engine
{
    
    class EntityBrowser {
    public: 

        EntityBrowser(const Ref<Scene>& scene) : m_Scene(scene) {}

        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

        void DrawTagComponent(Entity entity);
        void DrawTransformComponent(Entity entity);
        void DrawCameraComponent(Entity entity);
        void DrawSpriteComponent(Entity entity);
    private:
        Ref<Scene> m_Scene;
        Entity m_SelectedEntity;
    }; 

} // namespace Engine



#endif // ENGINE_ENTITY_BROWSER_HPP