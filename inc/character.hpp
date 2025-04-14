// character.h
#pragma once

#include <SDL2/SDL_ttf.h>

#include "../inc/ends.hpp"
#include "../inc/wall.hpp"
#include "../inc/boost.hpp"
#include "../inc/types.hpp"

class Character {
private:
	int w = 20, h = 20;
	Position pos;
	Position nextPos;
	Vector speed = {0, 0};
	int moveStartTime = SDL_GetTicks64(), dashsRemaining = 2;
	Position moveStartPosition;
	int colorIntensity;
	double RATIO;

	TTF_Font *font = nullptr;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect nextRect;
	SDL_Rect rect[10];
	SDL_Renderer *renderer = nullptr;

public:
	Character(End *start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer);

	int grab = 0, walk = 0;
	Position collide = {0, 0};

	void render(int nb_walls, Wall *walls, int nbBoosts, Boost *boosts);
	void move(int nb_walls, Wall *walls, int nbBoosts, Boost *boosts);
	void calculateNextRect();
	void dash(Vector direction);
	void setup(End start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer);
};
