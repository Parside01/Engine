#ifndef ENGINE_ENTITY_BROWSER_HPP
#define ENGINE_ENTITY_BROWSER_HPP


#include "Engine/Scene/Scene.hpp"
#include "Engine/engine_precompile_headers.hpp"
#include "Engine/Scene/Entity.hpp"
#include <glm/glm.hpp>


namespace Engine
{
    
    class EntityBrowser {
    public: 

        EntityBrowser(const Ref<Scene>& scene) : m_Scene(scene) {}

        Entity GetSelectedEntity() const { return m_SelectedEntity; }
        void SetSelectedEntity(Entity entity) { m_SelectedEntity = entity; }

        void OnImGuiRender();
    private:

        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

        void DrawTagComponent(Entity entity);
        void DrawTransformComponent(Entity entity);
        void DrawCameraComponent(Entity entity);
        void DrawSpriteComponent(Entity entity);

    private: // TODO: Скорее всего надо будет вынести все функции этой секции в отдельный файл\либу.
        void DrawDragVec3(const std::string& label, glm::vec3& value, float defaultValue = 0.f, float columnWidth = 100.f);
    private:
        Ref<Scene> m_Scene;
        Entity m_SelectedEntity;
    }; 

} // namespace Engine



#endif // ENGINE_ENTITY_BROWSER_HPP