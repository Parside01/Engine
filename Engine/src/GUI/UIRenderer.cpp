#include "Engine/GUI/UIRenderer.hpp"

#include <imgui_internal.h>

#include "imgui.h"

namespace Engine
{

    UIRenderer::UIStyle UIRenderer::m_Style;


    void UIRenderer::DrawInputText(const char* label, std::string &input) {
        ImGui::PushID(label);

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, m_Style.Column_DefaultSize);

        ImGui::Text("%s", label);
        ImGui::NextColumn();
        ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 3});

        char buffer[m_Style.Input_DefautlBufferSize];
        memset(buffer, 0, sizeof(buffer));
        strcpy(buffer, input.c_str());

        if (ImGui::InputText("##", buffer, sizeof(buffer)))
            input = std::string(buffer);
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();
        ImGui::Columns(1);
        ImGui::PopID();
        ImGui::Spacing();
    }
} // namespace Engine
