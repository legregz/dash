#include "../inc/utils.hpp"
#include "../inc/ends.hpp"

End::End(int x, int y, bool start) : Element(x, y, 40, 40), start(start) {
	if (start)
		color = {200, 200, 0, 255};
	else
		color = {200, 0, 200, 255};
}

End::End() {}

void End::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void End::scale(int GAP[2], double RATIO) {
	scaleRect(&x, &y, &w, &h, GAP, RATIO);
	rect = {x - w / 2, y - h / 2, w, h};
}
