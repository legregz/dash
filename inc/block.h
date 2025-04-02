// block.h
#pragma once

#include <SDL2/SDL.h>

class Block {
private:
	int x, y, w, h;

	SDL_Color defaultColor = {100, 100, 100, 255};
	SDL_Color grabbedColor = {255, 255, 255, 255};
	SDL_Color collidedColor = {157, 175, 175, 255};
	SDL_Color color = defaultColor;

public:
	SDL_Rect rect;

	Block(int x, int y, int w, int h);

	void render(SDL_Renderer *renderer);

	void setup(int GAP[2], double RATIO);
};

void Block_setup(int size, Block blocks[], int GAP[2], double RATIO);
