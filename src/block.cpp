// #include <SDL2/SDL.h>

#include "../inc/utils.h"
#include "../inc/block.h"

Block::Block(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

void Block::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Block::setup(int GAP[2], double RATIO) {
	convert_SDL_Rect(&x, &y, &w, &h, GAP, RATIO);

	rect = {x, y, w, h};
}

void Block_setup(int nbBlocks, Block blocks[], int GAP[2], double RATIO) {
	for (int i = 0; i < nbBlocks; i++)
	{
		blocks[i].setup(GAP, RATIO);
	}
}
