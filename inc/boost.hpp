// boost.h
#pragma once

#include <SDL2/SDL.h>
#include "element.hpp"

class Boost : public Element {
public:
	Boost(int x, int y);

	void render(SDL_Renderer* renderer) override;

	void scale(int GAP[2], double RATIO) override;
};
