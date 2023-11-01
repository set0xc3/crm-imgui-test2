#include "imgui/imgui.h"

#include "ui/ui.h"

#include "app.h"

int
main(void)
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

  uint32_t window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
                          | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
  app_get()->sdl.window
      = SDL_CreateWindow("CRM", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 1280, 720, window_flags);
  app_get()->sdl.gl_context = SDL_GL_CreateContext(app_get()->sdl.window);

  imgui_init();

  SDL_Event sdl_event;
  while (!app_get()->is_quit) {
    while (SDL_PollEvent(&sdl_event)) {
      switch (sdl_event.type) {
      case SDL_QUIT:
        app_get()->is_quit = true;
      }
      ui_process_event(&sdl_event);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    ui_show();

    SDL_GL_SwapWindow(app_get()->sdl.window);
    SDL_Delay(1);
  }

  return 0;
}
