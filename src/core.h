#pragma once

#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <imgui.h>

#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl2.h>

struct Core {
  bool is_quit;
  struct {
    SDL_Window   *window;
    SDL_GLContext gl_context;
  } sdl;
};

Core *core_get();
