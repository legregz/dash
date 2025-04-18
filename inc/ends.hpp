// ends.h
#pragma once

#include <SDL2/SDL.h>
#include "element.hpp"

class End : public Element {
private:
	bool start;

public:
	End(int x, int y, bool start);

	End();

	void render(SDL_Renderer* renderer) override;

	void scale(int GAP[2], double RATIO) override;
};
