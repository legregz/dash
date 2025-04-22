// wall.hpp
#pragma once

#include "element.hpp"

class Wall : public Element {
private:
	SDL_Color defaultColor = {100, 100, 100, 255};
	SDL_Color grabbedColor = {255, 255, 255, 255};
	SDL_Color collidedColor = {157, 175, 175, 255};

public:
	Wall(int x, int y, int w, int h);

	void render(SDL_Renderer* renderer) override;

	void scale(int GAP[2], double RATIO) override;
};
