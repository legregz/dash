// SDL_utils.h
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define PI 3.141592653;

int init_SDL(SDL_Renderer **renderer, SDL_Window **window, TTF_Font **font);

void quit_SDL(SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font);
