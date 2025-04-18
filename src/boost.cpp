// #include <SDL2/SDL.h>

#include "../inc/utils.hpp"
#include "../inc/boost.hpp"

Boost::Boost(int x, int y) : Element(x, y, 20, 20) {color = {0, 200, 200, 255};}

void Boost::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void Boost::scale(int GAP[2], double RATIO) {
	scaleRect(&x, &y, &w, &h, GAP, RATIO);
	rect = {x - w / 2, y - h / 2, w, h};
}
