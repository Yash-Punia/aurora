#include "core/imguiwindow.h"

#include "engine.h"
#include "log.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

namespace aurora::core
{
    ImguiWindow::ImguiWindow() {}
    ImguiWindow::~ImguiWindow()
    {
        Shutdown();
    }

    void ImguiWindow::Create()
    {
        IMGUI_CHECKVERSION(); //Verify data structure of current files with imgui.cpp

        //Initialize ImGui
        ImGui::CreateContext();

        auto& window = Engine::Instance().GetWindow();
        ImGui_ImplSDL2_InitForOpenGL(window.GetSDLWindow(), window.GetGLContext());
        ImGui_ImplOpenGL3_Init("#version 410");
        // ImGuiIO io = ImGui::GetIO();
        // int w,h;
        // window.GetSize(w,h);
        // AURORA_TRACE("w: {}",w);
        // ImGui::GetIO().DisplaySize.x = w;
        // ImGui::GetIO().DisplaySize.y = h;
        // AURORA_TRACE("displaySize: {}", ImGui::GetIO().DisplaySize.x);   
    }

    void ImguiWindow::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ImguiWindow::HandleSDLEvent(SDL_Event& e)
    {
        ImGui_ImplSDL2_ProcessEvent(&e);
    }

    void ImguiWindow::BeginRender()
    {
        // ImGui::NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(Engine::Instance().GetWindow().GetSDLWindow());
        ImGui::NewFrame();
    }

    void ImguiWindow::EndRender()
    {
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
