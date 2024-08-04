#include "Engine/GUI/Panels/EntityBrowser.hpp"

#include <Engine/log/Log.hpp>

#include "Engine/Scene/Systems/TransformSystem.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Scene/SceneCamera.hpp"

#include "Engine/Scene/CameraComponent.hpp"
#include "Engine/Scene/BaseComponents.hpp"
#include "Engine/Scene/TransfromComponent.hpp"
#include "Engine/Scene/RenderableComponents.hpp"

#include "Engine/Utils.hpp"

#include "imgui.h"
#include "imgui_internal.h"

#include <yaml-cpp/yaml.h>
#include "Engine/GUI/UIRenderer.hpp"

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

        if (ImGui::BeginPopupContextWindow("Create Entity")) {
            if (ImGui::MenuItem("Create Entity")) 
                m_Scene->CreateEntity();
            ImGui::EndPopup();
        }
        ImGui::End();

        ImGui::Begin("Details");
        if (m_SelectedEntity) {
            DrawComponents(m_SelectedEntity); 
            if (ImGui::Button("Add Component", ImGui::CalcItemSize(ImVec2(0, 0), 0, 0))) ImGui::OpenPopup("Add Component");
            if (ImGui::BeginPopup("Add Component")) {
                if (ImGui::MenuItem("Transform")) {
                    m_SelectedEntity.AddComponent<TransformComponent>();
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Camera")) {
                    m_SelectedEntity.AddComponent<CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }
                if (ImGui::MenuItem("Sprite")) {
                    m_SelectedEntity.AddComponent<SpriteComponent>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
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

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete Entity")) entityDeleted = true;
            ImGui::EndPopup();
        }

        if (isOpen) {
            ImGui::TreePop();
        } 

        // Всегда делать в конце отрисовки, иначе могут быть проблемы.
        if (!entityDeleted) return; 
        if (m_SelectedEntity == entity) m_SelectedEntity = {};
        m_Scene->RemoveEntity(entity);
    }

    void EntityBrowser::DrawComponents(Entity entity) {
        if (ImGui::Button("Load")) TextureLoader::GetTextureManager().GetTextureAtlas()->WriteAtlasInFile("../out.png");
        if (entity.HasComponent<TagComponent>())       DrawTagComponent(entity);
        if (entity.HasComponent<TransformComponent>()) DrawTransformComponent(entity);
        if (entity.HasComponent<CameraComponent>())    DrawCameraComponent(entity);
        if (entity.HasComponent<SpriteComponent>())    DrawSpriteComponent(entity); 
    }

    void EntityBrowser::DrawDragVec3(const std::string& label, glm::vec3& value, float defaultValue, float columnWidth) {
        ImGui::PushID(label.c_str());
        ImGui::Spacing();

        ImGui::Columns(2, 0, false);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 3});

        float lineHeight = ImGui::GetTextLineHeightWithSpacing();
        ImVec2 buttonSize = {lineHeight + 5.0f, lineHeight + 5.0f};

        auto drawVec3Line = [&](const std::string& axis, float& value, const ImVec4& color) {
            ImGui::PushStyleColor(ImGuiCol_Button, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{color.x + 0.1f, color.y + 0.1f, color.z + 0.1f, color.w});
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
            if (ImGui::Button(axis.c_str(), buttonSize)) {
                value = defaultValue;
            }
            ImGui::PopStyleColor(3);
            ImGui::SameLine(0.f, 5.f);
            ImGui::DragFloat(("##" + axis).c_str(), &value, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine(0, 5.f);
        };

        drawVec3Line("X", value.x, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        drawVec3Line("Y", value.y, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        drawVec3Line("Z", value.z, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});

        ImGui::PopStyleVar();
        ImGui::Columns(1);
        ImGui::PopID();
    }


    void EntityBrowser::DrawSpriteComponent(Entity entity) {
        auto& sprite = entity.GetComponent<SpriteComponent>();

        if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::ColorEdit4("Color", glm::value_ptr(sprite.Color));
            ImGui::Button("Texture", {100.f, 0.f});

            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {
                    const char* path = static_cast<char*>(payload->Data);
                    std::filesystem::path texturePath(path);
                    Ref<Texture2D> texture = TextureLoader::LoadTexture2DFromFile(texturePath.string());
                    sprite.Texture = texture;
                }
                ImGui::EndDragDropTarget();
            }
        }
    }

    void EntityBrowser::DrawTagComponent(Entity entity) {
        auto& tag = entity.GetComponent<TagComponent>();
        UIRenderer::DrawInputText("Tag", tag.Tag);
    }

    void EntityBrowser::DrawTransformComponent(Entity entity) {
        auto& transform = entity.GetComponent<TransformComponent>();
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed)) {
            bool deleteComponent{false};

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) ImGui::OpenPopup("Transform Menu");
            if (ImGui::BeginPopup("Transform Menu")) {
                if (ImGui::MenuItem("Delete Component")) deleteComponent = true;

                ImGui::EndPopup();
            }

            DrawDragVec3("Position", transform.Position);

            glm::vec3 euler = TransformSystem::QuatToEuler(transform.Rotation);
            DrawDragVec3("Rotation", euler);
            transform.Rotation = TransformSystem::EulerToQuat(euler);

            DrawDragVec3("Scale", transform.Scale);

            ImGui::Spacing();

            if (!deleteComponent) return;
            entity.RemoveCompoent<TransformComponent>();
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
