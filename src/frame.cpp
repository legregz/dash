#include "../inc/frame.hpp"

Frame::Frame() {}

Wall Frame::getWallAt(int index) const {
	return walls.at(index);
}

const std::vector<Wall>* Frame::getWalls() const {
	return &walls;
}

Boost Frame::getBoostAt(int index) const {
	return boosts.at(index);
}

// const Element& Frame::getOtherAt(int index) const {
// 	return others.at(index);
// }

// int Frame::getNumberOfOthers() const {
// 	return others.size();
// }

const End* Frame::getStart() const {
	return &start;
}

const End* Frame::getEnd() const {
	return &end;
}

void Frame::addWall(Wall wall) {
	walls.push_back(wall);
}

void Frame::addBoost(Boost boost) {
	boosts.push_back(boost);
}

// void Frame::addOthers(const Element& elt) {
// 	others.push_back(elt);
// }

void Frame::setStart(End start) {
	this->start = start;
}

void Frame::setEnd(End end) {
	this->end = end;
}

void Frame::render() {
	SDL_SetRenderTarget(renderer, texture);
	for (Wall wall : walls) {
		wall.render(renderer);
	}
	for (Boost boost : boosts) {
		boost.render(renderer);
	}
	// for (Element& elt : others) {
	// 	elt.render(renderer);
	// }
	start.render(renderer);
	end.render(renderer);
	SDL_SetRenderTarget(renderer, NULL);
}

void Frame::setup(SDL_Renderer* renderer, SDL_Texture* texture) {
	this->renderer = renderer;
	this->texture = texture;
}

void Frame::scale(int gap[2], double ratio) {
	for (Wall& wall : walls) {
		wall.scale(gap, ratio);
	}
	for (Boost& boost : boosts) {
		boost.scale(gap, ratio);
	}
	// for (Element& elt : others) {
	// 	elt.scale(gap, ratio);
	// }
	start.scale(gap, ratio);
	end.scale(gap, ratio);
}
