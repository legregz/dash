// #include <SDL2/SDL.h>

#include "../inc/utils.hpp"
#include "../inc/boost.hpp"

Boost::Boost(int x, int y) : x(x), y(y) {}

void Boost::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void Boost::setup(int GAP[2], double RATIO) {
	convert_SDL_Rect(&x, &y, &w, &h, GAP, RATIO);
	rect = {x - w / 2, y - h / 2, w, h};

	color = {0, 200, 200, 255};
}

void Boost_setup(int nbBoosts, Boost boosts[], int GAP[2], double RATIO) {
	for (int i = 0; i < nbBoosts; i++)
	{
		boosts[i].setup(GAP, RATIO);
	}
}
