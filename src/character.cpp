// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL.h>

#include "../inc/character.hpp"
// #include "../inc/ends.h"
// #include "../inc/wall.h"
#include "../inc/utils.hpp"
#include <SDL2/SDL_stdinc.h>


Character::Character(End *start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer) { setup(*start, GAP, RATIO, font, renderer); }

void Character::render(int nbWalls, Wall *walls, int nbBoosts, Boost *boosts) {
	for (int i = 9; i > 0; i--)
		rect[i] = rect[i - 1];

	move(nbWalls, walls, nbBoosts, boosts);

	// if (speed.y > 0)
	// 	speed.y -= 1;
	//

	for (int i = 9; i > -1; i--)
	{
		colorIntensity = 10 - i;
		SDL_SetRenderDrawColor(renderer, color.r / 10 * colorIntensity, color.g / 10 * colorIntensity, color.b / 10 * colorIntensity, color.a);
		SDL_RenderFillRect(renderer, &rect[i]);
	}
}

void Character::move(int nbWalls, Wall *walls, int nbBoosts, Boost *boosts) {
	calculateNextRect();
	int i = 0;
	collideX = 0;
	if (collideY == 1) {
		moveStartTime = SDL_GetTicks64();
	}
	collideY = 0;
	color = {255, 255, 255, 255};

	for (i = 0; i < nbWalls; i++) {
		SDL_Rect wallRect = walls[i].rect;

		if (SDL_HasIntersection(&wallRect, &nextRect)) {
			if (pos.x > wallRect.x + wallRect.w) {
				pos.x = wallRect.x + wallRect.w + w / 2 - 1;
				speed.x = 0;
			}

			if (pos.x < wallRect.x) {
				pos.x = wallRect.x - w / 2 + 1;
				speed.x = 0;
			}

			if (pos.y > wallRect.y + wallRect.h) {
				pos.y = wallRect.y + wallRect.h + h / 2 - 1;
				if (speed.x > 0)
					speed.x -= 1;
			}

			if (pos.y < wallRect.y) {
				pos.y = wallRect.y - h / 2 + 1;
				speed.y = 0;
				if (speed.x > 0)
					speed.x -= 1;
			}

			rect[0] = {pos.x - w / 2, pos.y - h / 2, w, h};
		}

		if (SDL_HasIntersection(&wallRect, &rect[0])) {
			if (pos.x > wallRect.x + wallRect.w)
				collideX = -1;

			if (pos.x < wallRect.x)
				collideX = 1;

			if (pos.y > wallRect.y + wallRect.h)
				collideY = -1;

			if (pos.y < wallRect.y) {
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

	if (((collideY == -1 && pos.y - nextY < 0) || (collideY == 1 && pos.y - nextY > 0) || collideY == 0) && (!grab || collideX == 0))
		pos.y = nextY;

	if ((collideX == -1 && pos.x - nextX < 0) || (collideX == 1 && pos.x - nextX > 0) || collideX == 0)
		pos.x = nextX;

	rect[0] = {pos.x - w / 2, pos.y - h / 2, w, h};
}

void Character::calculateNextRect() {
	// nextX = pos.x + cos(angle) * speed.x * RATIO + 10 * walk;
	// nextY = pos.y + sin(angle) * speed.y * RATIO + std::max(0, (int)RATIO * (20 - speed.y));
	double t;
	!(collideY == 1) ? t = (double)(SDL_GetTicks64() - moveStartTime) / 1000 : t = 0;
	nextX = speed.x * (t + 1) + pos.x + (collideY == 1 ? walk * 10 : 0);
	nextY = 0.5 * gravityVector.y / 1000 * pow(t, 2) + speed.y * (t + 1) + pos.y;
	// std::cout << "nextX : " << nextX << " nextY : " << nextY << " pos.x : " << pos.x << " pos.y : " << pos.y << " t : " << t << " collideX : " << collideX << " collideY : " << collideY << std::endl;
	nextRect = {nextX - w / 2, nextY - h / 2, w, h};
}

void Character::dash(Vector direction) {
	// if (SDL_GetTicks64() > (Uint64)moveStartTime + 200 && dashsRemaining != 0) {
		moveStartTime = SDL_GetTicks64();
		speed.x = 4 * direction.x;
		speed.y = 4 * direction.y;
		dashsRemaining -= 1;
		grab = 0;
	// }
}

void Character::setup(End start, int GAP[2], double RATIO, TTF_Font *font, SDL_Renderer *renderer) {
	pos.x = start.x, pos.y = start.y;
	convert_SDL_Rect(&pos.x, &pos.y - GAP[1], &w, &h, GAP, RATIO);
	this->RATIO = RATIO;
	this->font = font;
	this->renderer = renderer;
}
