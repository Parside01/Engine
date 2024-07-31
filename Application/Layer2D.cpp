#include "Layer2D.hpp"

#include "Engine/engine.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/ext/matrix_transform.hpp>


void Layer2D::OnAttach() {
    EG_PROFILE_FUNC();
    m_Texture2D = Engine::Texture2D::Create("assets/textures/ChessBoard.jpeg");

    Engine::FramebufferSpec data{};
    data.Attachments = { Engine::FramebufferTextureFormat::RGBA8, Engine::FramebufferTextureFormat::RED_INTEGER, Engine::FramebufferTextureFormat::Depth };
    data.Height = 720;
    data.Width = 1280;
    m_Framebuffer = Engine::FrameBuffer::Create(data);

    m_ESquere = m_MainScene->CreateEntity("Square Entity");
    m_ESquere.AddComponent<Engine::SpriteComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    m_ECamera = m_MainScene->CreateEntity("Main Camera");
    m_ECamera.AddComponent<Engine::CameraComponent>();

    m_EQuad = m_MainScene->CreateEntity("Quad Entity");
    m_EQuad.AddComponent<Engine::SpriteComponent>(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
    auto& transform = m_EQuad.GetComponent<Engine::TransformComponent>();
    transform.Position.x -= 3.f;
}

void Layer2D::OnDetach() {
    
}

void Layer2D::OnEvent(Engine::Event &event) {
    EG_PROFILE_FUNC();
    m_EditorCamera.OnEvent(event);

    Engine::EventDispatcher dispatcher(event); 
    dispatcher.Dispatch<Engine::MouseButtonPressedEvent>(EG_BINDEVENT(Layer2D::OnMouseButtonPressed));
}

bool Layer2D::OnMouseButtonPressed(Engine::MouseButtonPressedEvent& event) {
    if (event.GetMouseButton() == EG_MOUSE_BUTTON_LEFT) {
        if (m_ViewportHovered && !ImGuizmo::IsOver())
            m_EntityBrowser.SetSelectedEntity(m_HoveredEntity);
    }
    return false;
}

void Layer2D::OnUpdate(Engine::Timestep tick) {
    EG_PROFILE_FUNC();

    Tick = tick; 

    m_Framebuffer->SetSize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
    m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
    m_MainScene->OnViewportResize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));

    if (m_ViewportFocused)
        m_EditorCamera.OnUpdate(tick);

    m_Framebuffer->Bind();
    
    Engine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Engine::RenderCommand::Clear();

    m_Framebuffer->ClearAttachment(1, -1);

    m_MainScene->OnUpdateRuntime(tick);
    m_MainScene->OnUpdateEditor(tick, m_EditorCamera);

   { 
        // TODO: Вот эту фигню надо вынести в отдельную систему, и определять кликнутый объект не каждый кадр а только когда это нужно.
        EG_PROFILE_SCOPE("Definition of HoveredEntity");
        auto [x, y] = ImGui::GetMousePos();
        x -= m_ViewportBounds[0].x;
        y -= m_ViewportBounds[0].y;
        
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        y = viewportSize.y - y;
        int mx = round(x);
        int my = round(y);
        
        if ((mx >= 0 && my >= 0 && mx < viewportSize.x && my < viewportSize.y)) {
            int pixelData = m_Framebuffer->ReadFromPixel(1, mx, my);
            m_HoveredEntity = (pixelData == -1 ? Engine::Entity() : Engine::Entity(static_cast<entt::entity>(pixelData), m_MainScene.get()));
        }  
    }

    m_Framebuffer->Unbind();
}

void Layer2D::OnImGuiRender() {
    EG_PROFILE_FUNC();

    static bool opt_fullscreen = true;
    static bool p_open = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
            if (ImGui::MenuItem("Flag: NoDockingSplit",         "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0))             { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
            if (ImGui::MenuItem("Flag: NoUndocking",            "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
            if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                   { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
            if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))             { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
            if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
            ImGui::Separator();

            if (ImGui::MenuItem("Close", nullptr, false))
                p_open = false;
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    m_EntityBrowser.OnImGuiRender();

    ImGui::Begin("Viewport");
    {
        ImVec2 viewportMinRegion = ImGui::GetWindowContentRegionMin();
        ImVec2 viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        
        ImVec2 viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y};
        m_ViewportBounds[1] = {viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y};

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Engine::Application::GetApplication().GetGuiLayer().BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.f, 0.f});
        ImVec2 imVec = ImGui::GetContentRegionAvail();
        glm::vec2 viewportSize(imVec.x, imVec.y);
        if (m_ViewportSize != viewportSize) {
            m_ViewportSize = {viewportSize.x, viewportSize.y};
            m_EditorCamera.SetViewportSize(static_cast<float>(viewportSize.x), static_cast<float>(viewportSize.y));
        }

        uint32_t textureID = m_Framebuffer->GetColorAttachment();
        ImGui::Image(reinterpret_cast<void *>(textureID), {m_ViewportSize.x, m_ViewportSize.y}, {0.0f, 1.0f}, {1.0f, 0.0f});

        Engine::Entity selectedEntity = m_EntityBrowser.GetSelectedEntity();
        if (selectedEntity) {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

            const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
            glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();
            
            auto& tc = selectedEntity.GetComponent<Engine::TransformComponent>();
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), tc.Position) * glm::mat4_cast(tc.Rotation) * glm::scale(glm::mat4(1.f), tc.Scale);

            float snapValue = 0.5f; 
            if (m_GuizmoOperation == ImGuizmo::OPERATION::ROTATE) snapValue = 45.f;
            float snapValues[3] = {snapValue, snapValue, snapValue};

            ImGuizmo::Manipulate(
                glm::value_ptr(cameraView), 
                glm::value_ptr(cameraProjection), /*static_cast<ImGuizmo::OPERATION>(m_GuizmoOperation) */ImGuizmo::OPERATION::TRANSLATE, 
                ImGuizmo::LOCAL, 
                glm::value_ptr(transform)
            );
            if (ImGuizmo::IsUsing()) {
                EG_PROFILE_SCOPE("Decompose matrix ImGuizmo");
                glm::vec3 scale, position, skew; 
                glm::quat rotation;
                glm::vec4 perspective;

                glm::decompose(transform, scale, rotation, position, skew, perspective);

                tc.Position = position;
                tc.Rotation = rotation; 
                tc.Scale = scale;
            }
        } 

        ImGui::PopStyleVar();
    }
    ImGui::End();

    ImGui::End();
}