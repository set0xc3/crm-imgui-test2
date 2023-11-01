#include "ui.h"

void
ui_show()
{
  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  {
    // MenuBar
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Windows")) {
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::Begin("root_window", NULL,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
                     | ImGuiWindowFlags_NoSavedSettings
                     | ImGuiWindowFlags_NoInputs);
    {
      clients_view_show();
      sidebar_panel_show();

      ImGui::Begin("view", NULL,
                   ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
                       | ImGuiWindowFlags_NoSavedSettings);
      ImGui::End();

      ImGui::ShowDemoWindow();
    }
    ImGui::End();
  }
  ImGui::Render();
  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void
ui_process_event(SDL_Event *sdl_event)
{
  ImGui_ImplSDL2_ProcessEvent(sdl_event);
}
