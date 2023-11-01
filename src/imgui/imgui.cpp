#include "imgui.h"

#include "ui/ui.h"

#include "app.h"

static float font_size         = 16.0f;
static float display_dpi       = 0.0f;
static float display_dpi_scale = 2.0f;

void
imgui_init(void)
{
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // TODO:
  {
    SDL_GetDisplayDPI(0, NULL, NULL, &display_dpi);
    display_dpi = (display_dpi / 96);
  }

  ImGuiStyle &style = ImGui::GetStyle();
  style.ScaleAllSizes(display_dpi);

  // TODO: load font from memory
  ImFont *font = io.Fonts->AddFontFromFileTTF(
      "assets/fonts/Inter-Regular.otf", font_size * display_dpi_scale, NULL,
      io.Fonts->GetGlyphRangesCyrillic());

  ImGui::StyleColorsLight();
  imgui_set_custom_theme_colors();

  ImGui_ImplSDL2_InitForOpenGL(app_get()->sdl.window,
                               app_get()->sdl.gl_context);
  ImGui_ImplOpenGL2_Init();
}

void
imgui_set_custom_theme_colors(void)
{
  ImGuiStyle &style = ImGui::GetStyle();

  // Border
  style.FrameBorderSize = false;
  style.TabBorderSize   = true;

  // Rounding
  style.WindowRounding    = 4;
  style.ChildRounding     = 4;
  style.FrameRounding     = 4;
  style.PopupRounding     = 4;
  style.ScrollbarRounding = 4;
  style.GrabRounding      = 4;
  style.TabRounding       = 4;

#if 0
  style.Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

  // Headers
  style.Colors[ImGuiCol_Header]        = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
  style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
  style.Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

  // Buttons
  style.Colors[ImGuiCol_Button]        = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
  style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

  // Frame BG
  style.Colors[ImGuiCol_FrameBg]        = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
  style.Colors[ImGuiCol_FrameBgActive]
      = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

  // Tabs
  style.Colors[ImGuiCol_Tab]          = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
  style.Colors[ImGuiCol_TabHovered]   = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
  style.Colors[ImGuiCol_TabActive]    = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
  style.Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
  style.Colors[ImGuiCol_TabUnfocusedActive]
      = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

  // Title
  style.Colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
  style.Colors[ImGuiCol_TitleBgActive]
      = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
  style.Colors[ImGuiCol_TitleBgCollapsed]
      = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

#endif
}
