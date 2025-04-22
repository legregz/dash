// frame.hpp
#pragma once

#include "boost.hpp"
#include "element.hpp"
#include "ends.hpp"
#include "wall.hpp"
#include <vector>

class Frame {
private:
	std::vector<Wall> walls;
	std::vector<Boost> boosts;
	std::vector<Element> others;
	End start, end;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

public:
	Frame();

	Wall getWallAt(int index) const;
	const std::vector<Wall>* getWalls() const;

	Boost getBoostAt(int index) const;
	// const std::vector<Boost>* getBoosts() const;

	// const Element& getOtherAt(int index) const;
	// int getNumberOfOthers() const;

	const End* getStart() const;
	const End* getEnd() const;

	void addWall(Wall wall);
	void addBoost(Boost boost);
	// void addOthers(const Element& elt);
	void setStart(End start);
	void setEnd(End end);

	void render();
	void setup(SDL_Renderer* renderer, SDL_Texture* texture);
	void scale(int gap[2], double ratio);
};
