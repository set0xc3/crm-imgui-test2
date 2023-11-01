#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <imgui.h>

#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl2.h>

void ui_show(void);
void ui_process_event(SDL_Event *sdl_event);

void ui_clients_view_show(void);
