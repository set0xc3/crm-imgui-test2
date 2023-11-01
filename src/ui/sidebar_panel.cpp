#include "ui.h"

enum {
  UI_TextFlags_PosLeft,
  UI_TextFlags_PosCenter,
  UI_TextFlags_PosRight,
};

enum {
  UI_CategoryView_Main,
  UI_CategoryView_Repairs,
  UI_CategoryView_Clients,
  UI_CategoryView_Products,
  UI_CategoryView_Finance,
  UI_CategoryView_Reports,
  UI_CategoryView_Tasks,
  UI_CategoryView_Settings,
};

void
sidebar_panel_show(void)
{
  static float sidebar_width = 0.0f;

  static ImGuiStyle      &style = ImGui::GetStyle();
  static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration
                                  | ImGuiWindowFlags_NoMove
                                  | ImGuiWindowFlags_NoSavedSettings;
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(
      ImVec2((viewport->WorkSize.x / 2) - (sidebar_width / 2),
             viewport->WorkPos.y + 14));
  // ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize
  // : viewport->Size);
  ImGui::Begin("sidebar_panel", NULL, flags);
  {
    ImGui::BeginGroup();
    {
      static ImVec2 button_size   = ImVec2(150, 50);
      ImVec4 button_default_color = ImGui::GetStyleColorVec4(ImGuiCol_Button);

      const char *button_labels[]
          = { "Главная", "Клиенты", "Ремонты", "Товары",
              "Финансы", "Отчёты",  "Задания", "Настройки" };

      static uint32_t category_current_idx = 0;

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
    sidebar_width = ImGui::GetItemRectSize().x;
  }
  ImGui::End();
}
