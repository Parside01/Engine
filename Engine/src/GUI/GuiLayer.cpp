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
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

        }

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

    void GuiLayer::OnUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::GetApplication();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
        
        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time; 

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        static bool show = true;

        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::EndFrame();
    }



    void GuiLayer::OnEvent(Event& event) {
        EventDispatcher disp(event);

        disp.Dispatch<MouseButtonPressedEvent>(EG_BINDEVENT(GuiLayer::OnMouseButtonPressedEvent));
        disp.Dispatch<MouseButtonReleasedEvent>(EG_BINDEVENT(GuiLayer::OnMouseButtonReleasedEvent));
        disp.Dispatch<MouseMovedEvent>(EG_BINDEVENT(GuiLayer::OnMouseMovedEvent));
        disp.Dispatch<MouseScrolledEvent>(EG_BINDEVENT(GuiLayer::OnMouseScrolledEvent));
        
        disp.Dispatch<WindowResizeEvent>(EG_BINDEVENT(GuiLayer::OnWindowResizeEvent));
        
        disp.Dispatch<KeyTypedEvent>(EG_BINDEVENT(GuiLayer::OnKeyTypedEvent));
        disp.Dispatch<KeyPressedEvent>(EG_BINDEVENT(GuiLayer::OnKeyPressedEvent));
        disp.Dispatch<KeyReleasedEvent>(EG_BINDEVENT(GuiLayer::OnKeyReleasedEvent));
    }

    bool GuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = true;
        
        return false;
    }
    bool GuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = false;
            
        return false;
    }
    bool GuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += event.GetXOffset();
        io.MouseWheel += event.GetYOffset();

        return false;
    }
    bool GuiLayer::OnMouseMovedEvent(MouseMovedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.GetX(), event.GetY());

        return false;
    }

    bool GuiLayer::OnKeyPressedEvent(KeyPressedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = true;

        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }
    bool GuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = false;

        return false;
    }

    bool GuiLayer::OnKeyTypedEvent(KeyTypedEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        int code = event.GetKeyCode();
        if (code > 0 && code < 0x10000) 
            io.AddInputCharacter((unsigned short)code);

        return false;
    }

    bool GuiLayer::OnWindowResizeEvent(WindowResizeEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize  = ImVec2(event.GetHeight(), event.GetWidth());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);


        return false;
    }
} // namespace Engine
