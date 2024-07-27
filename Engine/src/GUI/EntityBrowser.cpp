#include "Engine/GUI/EntityBrowser.hpp"
#include "Engine/Scene/Systems/TransformSystem.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Scene/SceneCamera.hpp"

#include "Engine/Scene/CameraComponent.hpp"
#include "Engine/Scene/BaseComponents.hpp"
#include "Engine/Scene/TransfromComponent.hpp"
#include "Engine/Scene/RenderableComponents.hpp"

#include "imgui.h"

namespace Engine
{
    
    void EntityBrowser::OnImGuiRender() {
        ImGui::Begin("Entity Browser");
        
        auto view = m_Scene->GetRegistry().view<TagComponent>();
        for (auto entityID : view) {
            Entity entity(entityID, m_Scene.get());
            DrawEntityNode(entity);
        } 
        if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered()) 
            m_SelectedEntity = {};
        ImGui::End();

        ImGui::Begin("Details");
        if (m_SelectedEntity) {
            DrawComponents(m_SelectedEntity); 
        }
        ImGui::End();
    }

    void EntityBrowser::DrawEntityNode(Entity entity) {
        std::string& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = (m_SelectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
        bool isOpen = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uint32_t>(entity)), flags, "%s", tag.c_str());
        if (ImGui::IsItemClicked()) {
            m_SelectedEntity = entity;
        }

        if (isOpen) {
            ImGui::TreePop();
        } 
    }

    void EntityBrowser::DrawComponents(Entity entity) {
        if (entity.HasComponent<TagComponent>())       DrawTagComponent(entity);
        if (entity.HasComponent<TransformComponent>()) DrawTransformComponent(entity);
        if (entity.HasComponent<CameraComponent>())    DrawCameraComponent(entity);
        if (entity.HasComponent<SpriteComponent>())    DrawSpriteComponent(entity); 
    }

    void EntityBrowser::DrawSpriteComponent(Entity entity) {
        auto& sprite = entity.GetComponent<SpriteComponent>();
        if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::ColorEdit4("Color", glm::value_ptr(sprite.Color));
        }
    }

    void EntityBrowser::DrawTagComponent(Entity entity) {
        auto& tag = entity.GetComponent<TagComponent>();
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, tag.Tag.c_str());
        if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
            tag.Tag = std::string(buffer);
        }
    }

    void EntityBrowser::DrawTransformComponent(Entity entity) {
        auto& transform = entity.GetComponent<TransformComponent>();

        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::DragFloat3("Position", glm::value_ptr(transform.Position));
            glm::vec3 euler = TransformSystem::QuatToEuler(transform.Rotation);
            if (ImGui::DragFloat3("Rotation", glm::value_ptr(euler), 1.f, -360.f, 360.f, "%.1f")) 
                transform.Rotation = TransformSystem::EulerToQuat(euler);
            
            ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale), 0.1f, 0.1f, 10.f, "%.1f");
        }
    }

    void EntityBrowser::DrawCameraComponent(Entity entity) {
        if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen)) {
            auto& cameraComponent = entity.GetComponent<CameraComponent>();
            const char* projectionType[] = {"Perspective", "Orthographic"};
            const char* currentProjectionType = projectionType[static_cast<int>(cameraComponent.Camera.GetProjectionType())];
            if (ImGui::BeginCombo("Camera Projection", currentProjectionType)) {
                for (uint32_t i{0}; i < 2; ++i) {
                    bool isSelected = currentProjectionType == projectionType[i];
                    if (ImGui::Selectable(projectionType[i], isSelected)) {
                        currentProjectionType = projectionType[i];
                        cameraComponent.Camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
                    }

                    if (isSelected) ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }
            if (cameraComponent.Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {
                float orthSize = cameraComponent.Camera.GetOrthographicSize();
                if (ImGui::DragFloat("Size", &orthSize)) cameraComponent.Camera.SetOrthographicSize(orthSize);

                float near = cameraComponent.Camera.GetOrthographicNear();
                if (ImGui::DragFloat("Near", &near)) cameraComponent.Camera.SetOrthographicNear(near);

                float far = cameraComponent.Camera.GetOrthographicFar();
                if (ImGui::DragFloat("Far", &far)) cameraComponent.Camera.SetOrthographicFar(far);
            }
            if (cameraComponent.Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
                float viewAngle = glm::degrees(cameraComponent.Camera.GetPerspectiveViewAngle());
                if (ImGui::DragFloat("View Angle", &viewAngle)) cameraComponent.Camera.SetPerspectiveViewAngle(glm::radians(viewAngle));
 
                float near = cameraComponent.Camera.GetPerspectiveNear();
                if (ImGui::DragFloat("Near", &near)) cameraComponent.Camera.SetPerspectiveNear(near);

                float far = cameraComponent.Camera.GetPerspectiveFar();
                if (ImGui::DragFloat("Far", &far)) cameraComponent.Camera.SetPerspectiveFar(far);
            }
            ImGui::Checkbox("Primary", &entity.GetComponent<CameraComponent>().IsPrimary);
            ImGui::Checkbox("Fixed Aspect Ratio", &entity.GetComponent<CameraComponent>().FixedAspectRatio);
        }

    }
} // namespace Engine
