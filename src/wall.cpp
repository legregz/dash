// #include <SDL2/SDL.h>

#include "../inc/utils.hpp"
#include "../inc/wall.hpp"

Wall::Wall(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

void Wall::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Wall::setup(int GAP[2], double RATIO) {
	convert_SDL_Rect(&x, &y, &w, &h, GAP, RATIO);

	rect = {x, y, w, h};
}

void Wall_setup(int nbWalls, Wall walls[], int GAP[2], double RATIO) {
	for (int i = 0; i < nbWalls; i++)
	{
		walls[i].setup(GAP, RATIO);
	}
}
