// elements.hpp
#pragma once

#include "types.hpp"
#include <SDL2/SDL.h>

class Element {
protected:
	int x, y, w, h;
	SDL_Color color;
	SDL_Rect rect;

public:
	Element(int x, int y, int w, int h);

	Element();

	int getX() const;
	int getY() const;
	Position getPos() const;
	SDL_Rect getRect() const;
	void setX(int x);
	void setY(int y);
	void setPos(Position pos);
	// void setRect(SDL_Rect rect);

	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void scale(int GAP[2], double RATIO) = 0;
};
