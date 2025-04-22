// character.h
#pragma once

#include <SDL2/SDL_ttf.h>
#include "../inc/ends.hpp"
#include "../inc/types.hpp"
#include "../inc/frame.hpp"

#define DASH_LIMIT 3;

class Character {
private:
	int w = 20, h = 20;
	Position pos;
	Position nextPos;
	Vector speed = {0, 0};
	long moveStartTime = SDL_GetTicks64(), dashAnimationEndTime = 0;
	Position moveStartPosition;
	int colorIntensity, dashsRemaining = DASH_LIMIT;
	double RATIO;

	TTF_Font *font = nullptr;
	SDL_Color color = {255, 255, 255, 255};
	SDL_Rect nextRect;
	SDL_Rect rect[10];
	SDL_Renderer *renderer = nullptr;

public:
	Character(const End* start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer);

	int grab = 0, walk = 0;
	Position collide = {0, 0};

	void render(Frame *frame);
	void move(Frame *frame);
	void calculateNextRect();
	void dash(Vector direction);
	void scale(const End* start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer);
};
