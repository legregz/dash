// SDL_utils.hpp
#pragma once

#include <SDL2/SDL_ttf.h>

int init_SDL(SDL_Renderer **renderer, SDL_Window **window, TTF_Font **font);

void quit_SDL(SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font);
