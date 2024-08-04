#include "Engine/GUI/Panels/ContentBrowser.hpp"

#include "Engine/Render/Texture/TextureLoader.hpp"

#include "imgui.h"

#include <filesystem>
#include <imgui_internal.h>


namespace Engine {
    static const std::filesystem::path s_AssetsDirectory = "../assets";

    ContentBrowser::ContentBrowser()
        : m_CurrentDir(s_AssetsDirectory) {
        m_DirIcon = TextureManager::CreateTexture("assets/textures/FolderIcon.png");
        m_FileIcon = TextureManager::CreateTexture("assets/textures/FileIcon.png");
    }

    void ContentBrowser::OnImGuiRender() {
        ImGui::Begin("Conten Browser");
        if (m_CurrentDir != std::filesystem::path(s_AssetsDirectory)) {
            if (ImGui::Button("Back...")) m_CurrentDir = m_CurrentDir.parent_path();
        }

        static float padding = 25.f;
        static float iconSize = 75.f;
        float cellSize = padding + iconSize;

        float pannelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = static_cast<int>(pannelWidth / cellSize);
        if (columnCount < 1) columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        for (auto &dir: std::filesystem::directory_iterator(m_CurrentDir)) {
            const std::filesystem::path &path = dir.path();
            std::string filename = path.filename().string();

            ImGui::PushID(filename.c_str());
            Ref<Texture2D> icon = dir.is_directory() ? m_DirIcon : m_FileIcon;
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            auto textureCoords = TextureManager::GetTextureCoords(icon);
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(TextureManager::GetRendererID(icon)), {iconSize, iconSize},
                               {textureCoords[0].x, textureCoords[3].y},
                               {textureCoords[2].x, textureCoords[1].y});

            if (ImGui::BeginDragDropSource()) {
                std::filesystem::path relativePath(path);
                const char *itemPath = relativePath.c_str();
                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (strlen(itemPath) + 1) * sizeof(char));
                ImGui::EndDragDropSource();
            }

            ImGui::PopStyleColor();

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (dir.is_directory())
                    m_CurrentDir /= path.filename();
            }

            ImVec2 textSize = ImGui::CalcTextSize(filename.c_str());
            float textOffsetX = (iconSize - textSize.x) * 0.5f; // Расчет смещения для центрирования
            ImVec2 cursorPos = ImGui::GetCursorPos();
            ImGui::SetCursorPosX(cursorPos.x + textOffsetX);
            ImGui::TextWrapped("%s", filename.c_str());

            ImGui::SetCursorPosX(cursorPos.x);
            ImGui::NextColumn();
            ImGui::PopID();
        }
        ImGui::Columns(1);
        ImGui::End();
    }
}
