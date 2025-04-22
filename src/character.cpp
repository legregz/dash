#include "../inc/character.hpp"
#include "../inc/utils.hpp"

Character::Character(const End* start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer) { scale(start, GAP, RATIO, font, renderer); }

void Character::render(Frame *frame) {
	for (int i = 9; i > 0; i--)
		rect[i] = rect[i - 1];

	move(frame);

	for (int i = 9; i > -1; i--)
	{
		colorIntensity = 10 - i;
		SDL_SetRenderDrawColor(renderer, color.r / 10 * colorIntensity, color.g / 10 * colorIntensity, color.b / 10 * colorIntensity, color.a);
		SDL_RenderFillRect(renderer, &rect[i]);
	}

	long timeDiff = (dashAnimationEndTime - SDL_GetTicks64());
	if (timeDiff > 0) {
		SDL_SetRenderDrawColor(renderer, color.r / 1000.0 * timeDiff, color.g / 1000.0 * timeDiff, color.b / 1000.0 * timeDiff, color.a);
		int squareRadius = (1000 - timeDiff) / 10;
		SDL_Rect dashRect = {moveStartPosition.x - rect[0].w / 2 - squareRadius / 2, moveStartPosition.y - rect[0].h / 2 - squareRadius / 2, rect[0].w + squareRadius, rect[0].h + squareRadius};
		SDL_RenderDrawRect(renderer, &dashRect);
	}
}

void Character::move(Frame *frame) {
	if (collide.y == 1 && !speed.y) {
		moveStartTime = SDL_GetTicks64();
		moveStartPosition = pos;
		dashsRemaining = DASH_LIMIT;
	}
	calculateNextRect();
	collide = {0, 0};
	Vector relativeWallPosition, direction = {0, 0};

	if (pos.x < nextPos.x) {
		direction.x = 1;
	} else if (pos.x > nextPos.x) {
		direction.x = -1;
	}

	if (pos.y < nextPos.y) {
		direction.y = 1;
	} else if (pos.y > nextPos.y) {
		direction.y = -1;
	}

	int i = 0;
	for (Wall wall : *frame->getWalls()) {
		i++;
		SDL_Rect wallRect = wall.getRect();
		relativeWallPosition = {0, 0};

		if (pos.x < wallRect.x) {
			relativeWallPosition.x = 1;
		} else if (pos.x > wallRect.x + wallRect.w) {
			relativeWallPosition.x = -1;
		}

		if (pos.y < wallRect.y) {
			relativeWallPosition.y = 1;
		} else if (pos.y > wallRect.y + wallRect.h) {
			relativeWallPosition.y = -1;
		}

		if (SDL_HasIntersection(&wallRect, &nextRect)) {
			if (relativeWallPosition.x == 1) {
				if (direction.x == 1) {
					pos.x = wallRect.x - w / 2 + 1;
					speed.x = 0;
					speed.y = 0;
					moveStartTime = SDL_GetTicks64();
					moveStartPosition = pos;
				}
				collide.x = 1;
			} else if (relativeWallPosition.x == -1) {
				if (direction.x == -1) {
					pos.x = wallRect.x + wallRect.w + w / 2 - 1;
					speed.x = 0;
					speed.y = 0;
					moveStartTime = SDL_GetTicks64();
					moveStartPosition = pos;
				}
				collide.x = -1;
			}

			if (relativeWallPosition.y == 1) {
				if (direction.y == 1) {
					pos.y = wallRect.y - h / 2 + 1;
					speed.y = 0;
				}
				collide.y = 1;
				// if (speed.x > 0)
				// 	speed.x -= 1;
			} else if (relativeWallPosition.y == -1) {
				if (direction.y == -1) {
					pos.y = wallRect.y + wallRect.h + h / 2 - 1;
					speed.y = 0;
					moveStartTime = SDL_GetTicks64();
					moveStartPosition = pos;
				}
				collide.y = -1;
				// if (speed.x > 0)
				// 	speed.x -= 1;
			}
		}
	}

	if (collide.x && grab) {
		dashsRemaining = DASH_LIMIT;
		moveStartTime = SDL_GetTicks64();
		moveStartPosition = pos;
	}

	if (((collide.y == -1 && direction.y == 1) || (collide.y == 1 && direction.y == -1) || collide.y == 0) && (!grab || collide.x == 0))
		pos.y = nextPos.y;

	if ((collide.x == -1 && direction.x == 1) || (collide.x == 1 && direction.x == -1) || collide.x == 0)
		pos.x = nextPos.x;

	rect[0] = {pos.x - w / 2, pos.y - h / 2, w, h};
}

void Character::calculateNextRect() {
	double t = (SDL_GetTicks64() - moveStartTime) / 100.0;
	nextPos.x = speed.x * t + moveStartPosition.x + (collide.y == 1 ? walk * 10 * RATIO : 0);
	nextPos.y = 0.5 * gravityVector.y / 500 * pow(t, 2) * RATIO + speed.y * t + moveStartPosition.y;
	nextRect = {nextPos.x - w / 2, nextPos.y - h / 2, w, h};
}

void Character::dash(Vector direction) {
	if (dashsRemaining != 0) { // SDL_GetTicks64() > (Uint64)moveStartTime + 200 &&
		moveStartTime = SDL_GetTicks64();
		dashAnimationEndTime = SDL_GetTicks64() + 1000;
		moveStartPosition = pos;
		speed.x = 50 * direction.x * RATIO;
		speed.y = 50 * direction.y * RATIO;
		dashsRemaining -= 1;
		grab = 0;
	}
}

void Character::scale(const End* start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer) {
	pos.x = start->getX(), pos.y = start->getY();
	scaleRect(&pos.x, &pos.y, &w, &h, GAP, RATIO);
	moveStartPosition = {pos.x, pos.y};
	this->RATIO = RATIO;
	this->font = font;
	this->renderer = renderer;
}
