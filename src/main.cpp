#include "core.h"

#include "imgui/imgui.h"

#include "ui/sidebar_panel.h"

int
main(void)
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  uint32_t window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
                          | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
  core_get()->sdl.window
      = SDL_CreateWindow("CRM", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 1280, 720, window_flags);
  core_get()->sdl.gl_context = SDL_GL_CreateContext(core_get()->sdl.window);

  imgui_init();

  SDL_Event sdl_event;
  while (!core_get()->is_quit) {
    while (SDL_PollEvent(&sdl_event)) {
      switch (sdl_event.type) {
      case SDL_QUIT:
        core_get()->is_quit = true;
      }
      ImGui_ImplSDL2_ProcessEvent(&sdl_event);
    }

    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(237.f / 255.f, 238.f / 255.f, 240.f / 255.f, 0);

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    {
      sidebar_panel_show();
      // ImGui::ShowDemoWindow();
    }
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(core_get()->sdl.window);
    SDL_Delay(1);
  }

  return 0;
}
