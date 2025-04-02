// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL.h>

#include "../inc/character.h"
// #include "../inc/ends.h"
// #include "../inc/block.h"
#include "../inc/utils.h"
#include <SDL2/SDL_stdinc.h>

Character::Character(End *start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer) { setup(*start, GAP, RATIO, font, renderer); }

void Character::render(int nbBlocks, Block *blocks, int nbBoosts, Boost *boosts) {
	for (int i = 9; i > 0; i--)
		rect[i] = rect[i - 1];

	move(nbBlocks, blocks, nbBoosts, boosts);

	if (speedY > 0)
		speedY -= 1;

	for (int i = 9; i > -1; i--)
	{
		colorIntensity = 10 - i;
		SDL_SetRenderDrawColor(renderer, color.r / 10 * colorIntensity, color.g / 10 * colorIntensity, color.b / 10 * colorIntensity, color.a);
		SDL_RenderFillRect(renderer, &rect[i]);
	}
}

void Character::move(int nbBlocks, Block *blocks, int nbBoosts, Boost *boosts) {
	calculateNextRect();
	int i = 0;
	collideX = 0;
	collideY = 0;
	color = {255, 255, 255, 255};

	for (i = 0; i < nbBlocks; i++) {
		SDL_Rect blockRect = blocks[i].rect;

		if (SDL_HasIntersection(&blockRect, &nextRect)) {
			if (x > blockRect.x + blockRect.w) {
				x = blockRect.x + blockRect.w + w / 2 - 1;
				speedX = 0;
			}

			if (x < blockRect.x) {
				x = blockRect.x - w / 2 + 1;
				speedX = 0;
			}

			if (y > blockRect.y + blockRect.h) {
				y = blockRect.y + blockRect.h + h / 2 - 1;
				if (speedX > 0)
					speedX -= 1;
			}

			if (y < blockRect.y) {
				y = blockRect.y - h / 2 + 1;
				speedY = 0;
				if (speedX > 0)
					speedX -= 1;
			}

			rect[0] = {x - w / 2, y - h / 2, w, h};
		}

		if (SDL_HasIntersection(&blockRect, &rect[0])) {
			if (x > blockRect.x + blockRect.w)
				collideX = -1;

			if (x < blockRect.x)
				collideX = 1;

			if (y > blockRect.y + blockRect.h)
				collideY = -1;

			if (y < blockRect.y) {
				collideY = 1;
				dashsRemaining = 2;
			}
			if (grab)
				dashsRemaining = 2;
		}
	}

	// if (collideX)
	// 	color = {255, 0, 0, 255};
	// if (collideY)
	// 	color = {255, 255, 0, 255};

	if (((collideY == -1 && y - nextY < 0) || (collideY == 1 && y - nextY > 0) || collideY == 0) && (!grab || collideX == 0))
		y = nextY;

	if ((collideX == -1 && x - nextX < 0) || (collideX == 1 && x - nextX > 0) || collideX == 0)
		x = nextX;

	rect[0] = {x - w / 2, y - h / 2, w, h};
}

void Character::calculateNextRect() {
	nextX = x + cos(angle) * speedX * RATIO + 10 * walk;
	nextY = y + sin(angle) * speedY * RATIO + std::max(0, (int)RATIO * (10 - speedY));
	nextRect = {nextX - w / 2, nextY - h / 2, w, h};
}

void Character::dash(int x, int y) {
	if (SDL_GetTicks64() > (Uint64)dashDelay + 200 && dashsRemaining != 0) {
		dashDelay = SDL_GetTicks64();
		speedX = 10;
		speedY = 15;
		angle = atan2(y, x);
		dashsRemaining -= 1;
		grab = 0;
	}
}

void Character::setup(End start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer) {
	x = start.x, y = start.y;
	convert_SDL_Rect(&x, &y, &w, &h, GAP, RATIO);
	this->RATIO = RATIO;
	this->font = font;
	this->renderer = renderer;
}
