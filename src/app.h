#pragma once

#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_opengl.h>

struct App {
  bool is_quit;
  struct {
    SDL_Window   *window;
    SDL_GLContext gl_context;
  } sdl;
};

App *app_get();
