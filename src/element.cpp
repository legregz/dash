#include "../inc/element.hpp"
#include "../inc/types.hpp"
#include <cstdio>

Element::Element(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), rect({x, y, w, h}) {}

Element::Element() {}

int Element::getX() const {
	return x;
}

int Element::getY() const {
	return y;
}

Position Element::getPos() const {
	return {x, y};
}

SDL_Rect Element::getRect() const {
	return rect;
}

void Element::setX(int x) {
	this->x = x;
}

void Element::setY(int y) {
	this->y = y;
}

void Element::setPos(Position pos) {
	x = pos.x;
	y = pos.y;
}
