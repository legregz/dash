// boost.h
#pragma once

#include <SDL2/SDL.h>

class Boost {
private:
	int w = 20, h = 20;

	SDL_Color color;

public:
	int x, y;
	SDL_Rect rect;

	Boost(int x, int y);

	void render(SDL_Renderer *renderer);

	void setup(int GAP[2], double RATIO);
};

void Boost_setup(int nbBoosts, Boost boosts[], int GAP[2], double RATIO);
