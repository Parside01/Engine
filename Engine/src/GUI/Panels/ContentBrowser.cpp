#include "Engine/GUI/Panels/ContentBrowser.hpp"


#include "imgui.h"

#include <filesystem>


namespace Engine {

    static const std::filesystem::path s_AssetsDirectory = "../assets";

    ContentBrowser::ContentBrowser()
        : m_CurrentDir(s_AssetsDirectory)
    {
        m_DirIcon = Texture2D::Create("assets/textures/FolderIcon.png");
        m_FileIcon = Texture2D::Create("assets/textures/FileIcon.png");
    }

    void ContentBrowser::OnImGuiRender() {
        ImGui::Begin("Conten Browser");
        if (m_CurrentDir != std::filesystem::path(s_AssetsDirectory)) {
            if (ImGui::Button("Back...")) m_CurrentDir = m_CurrentDir.parent_path();
        }    

        static float padding = 16.f;
        static float iconSize = 110.f;
        float cellSize = padding + iconSize;

        float pannelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = static_cast<int>(pannelWidth / cellSize);
        if (columnCount < 1) columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        for (auto& dir : std::filesystem::directory_iterator(m_CurrentDir)) {
            const std::filesystem::path& path = dir.path();
            std::string filename = path.filename().string();

            ImGui::PushID(filename.c_str());
            Ref<Texture2D> icon = dir.is_directory() ? m_DirIcon : m_FileIcon;
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(icon->GetTextureID()), {iconSize, iconSize}, {0, 1}, {1, 0});

            if (ImGui::BeginDragDropSource()) {
                std::filesystem::path relativePath(path);
                const char* itemPath = relativePath.c_str();
                ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (strlen(itemPath) + 1) * sizeof(char));
                ImGui::EndDragDropSource();
            }

            ImGui::PopStyleColor();

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (dir.is_directory())
                    m_CurrentDir /= path.filename();
            }

            ImGui::TextWrapped(filename.c_str());
            ImGui::NextColumn();
            ImGui::PopID();
        }
        ImGui::Columns(1);
        ImGui::End();
    }
}
