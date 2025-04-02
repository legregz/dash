// character.h
#pragma once

#include <SDL2/SDL_ttf.h>

#include "../inc/ends.h"
#include "../inc/block.h"
#include "../inc/boost.h"

#define PI 3.141592653;

class Character {
private:
	int x, y, w = 20, h = 20;
	int nextX, nextY, speedX = 0, speedY = 0;
	int dashDelay = SDL_GetTicks64(), dashsRemaining = 2;
	int colorIntensity;
	double RATIO, angle = 0.5 * PI;

	TTF_Font *font = nullptr;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect nextRect;
	SDL_Rect rect[10];
	SDL_Renderer *renderer = nullptr;

public:
	Character(End *start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer);

	int grab = 0, walk = 0, collideX = 0, collideY = 0;

	void render(int nb_blocks, Block *blocks, int nbBoosts, Boost *boosts);
	void move(int nb_blocks, Block *blocks, int nbBoosts, Boost *boosts);
	void calculateNextRect();
	void dash(int x, int y);
	void setup(End start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer);
};
