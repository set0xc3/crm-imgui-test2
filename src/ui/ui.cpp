#include "ui.h"
#include "imgui.h"

enum {
  UI_TextFlags_PosLeft,
  UI_TextFlags_PosCenter,
  UI_TextFlags_PosRight,
};

enum {
  UI_CategoryView_Main,
  UI_CategoryView_Clients,
  UI_CategoryView_Repairs,
  UI_CategoryView_Products,
  UI_CategoryView_Finance,
  UI_CategoryView_Reports,
  UI_CategoryView_Tasks,
  UI_CategoryView_Settings,
};

static uint32_t category_current_idx;

const char *button_labels[] = {
  "Главная", "Клиенты", "Ремонты", "Товары",
  "Финансы", "Отчёты",  "Задания", "Настройки",
};

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
      static ImVec2 sidebar_size;

      static ImGuiStyle &style = ImGui::GetStyle();
      ImGui::SetNextWindowPos(
          ImVec2((viewport->WorkSize.x / 2) - (sidebar_size.x / 2),
                 viewport->WorkPos.y + 14));
      ImGui::Begin("sidebar_panel", NULL,
                   ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
                       | ImGuiWindowFlags_NoSavedSettings
                       | ImGuiWindowFlags_NoBackground);
      {
        ImGui::BeginGroup();
        {
          static ImVec2 button_size = ImVec2(150, 50);
          ImVec4        button_default_color
              = ImGui::GetStyleColorVec4(ImGuiCol_Button);

          for (uint32_t i = 0;
               i < sizeof(button_labels) / sizeof(button_labels[0]); i++) {
            if (category_current_idx == i) {
              ImGui::PushStyleColor(ImGuiCol_Button, button_default_color);
            } else {
              ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            }

            if (ImGui::Button(button_labels[i])) {
              category_current_idx = i;
            }
            ImGui::SameLine();

            ImGui::PopStyleColor();
          }
        }
        ImGui::EndGroup();
        sidebar_size = ImGui::GetItemRectSize();
      }
      ImGui::End();

      ImGui::SetNextWindowPos(ImVec2(14, viewport->WorkPos.y + 100));
      ImGui::SetNextWindowSize(
          ImVec2(viewport->WorkSize.x - 28, viewport->WorkSize.y - 114));

      ImGui::Begin("view", NULL,
                   ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
                       | ImGuiWindowFlags_NoSavedSettings);
      {
        if (category_current_idx == UI_CategoryView_Clients) {
          ui_clients_view_show();
        }
      }
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
