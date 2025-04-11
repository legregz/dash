// #include <SDL2/SDL.h>

#include "../inc/utils.hpp"
#include "../inc/ends.hpp"

End::End(int x, int y) : x(x), y(y) {}

void End::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void End::setup(int GAP[2], double RATIO, int start) {
	convert_SDL_Rect(&x, &y, &w, &h, GAP, RATIO);
	rect = {x - w / 2, y - h / 2, w, h};

	if (start)
		color = {200, 200, 0, 255};
	else
		color = {200, 0, 200, 255};
}

void End_setup(End *start, End *end, int GAP[2], double RATIO) {
	start->setup(GAP, RATIO, 1);
	end->setup(GAP, RATIO, 0);
}
