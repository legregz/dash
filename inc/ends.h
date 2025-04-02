// ends.h
#pragma once

#include <SDL2/SDL.h>

class End {
private:
	int w = 40, h = 40, start;

	SDL_Color color;

public:
	int x, y;
	SDL_Rect rect;

	End(int x, int y);

	void render(SDL_Renderer *renderer);

	void setup(int GAP[2], double RATIO, int start);
};

void End_setup(End *start, End *end, int GAP[2], double RATIO);
