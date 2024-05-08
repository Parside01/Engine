// #include "../include/GUI/GuiLayer.hpp"
// #include "../include/engine_precompile_headers.hpp"

#include "Engine/GUI/GuiLayer.hpp"
#include "Engine/engine_precompile_headers.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

namespace Engine
{
    GuiLayer::GuiLayer() 
    : Layer("GUI_Layer") {

    }

    GuiLayer::~GuiLayer() {
        
    }

    void GuiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        // Переключить на другую ветку.
        // Без них нельзя закреплять вкладки и тд.
        // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        float fontSize = 18.f; 
        io.Fonts->AddFontFromFileTTF("assets/fonts/JetBrainsMono.ttf", fontSize);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/JetBrainsMono.ttf", fontSize);


        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();

        // Переключить на другую ветку.
        // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

        // }

        SetDarkTheme();

        Application& app = Application::GetApplication();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    void GuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GuiLayer::OnEvent(Event& event) {
        if (m_BlockEvents)
		{   
			ImGuiIO& io = ImGui::GetIO();
			event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
    }

   void GuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
   }

   void GuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();

        Application& app = Application::GetApplication();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetHeight(), float(app.GetWindow().GetWidth()));

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Переключить на другую ветку.
        // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        //     GLFWwindow* ctx = glfwGetCurrentContext();
        // }
   }

   uint32_t GuiLayer::GetActiveWidgetID() const { return 0; }
} // namespace Engine
