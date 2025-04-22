// #include <SDL2/SDL.h>

#include "../inc/utils.hpp"
#include "../inc/wall.hpp"

Wall::Wall(int x, int y, int w, int h) : Element(x, y, w, h) {
	color = defaultColor;
}

void Wall::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Wall::scale(int GAP[2], double RATIO) {
	scaleRect(&x, &y, &w, &h, GAP, RATIO);
	rect = {x, y, w, h};
	// printf("&x : %p\n", &this->x);
}
