// boost.hpp
#pragma once

#include "element.hpp"

class Boost : public Element {
public:
	Boost(int x, int y);

	void render(SDL_Renderer* renderer) override;

	void scale(int GAP[2], double RATIO) override;
};
