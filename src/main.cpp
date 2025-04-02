//#include <SDL2/SDL.h>

#include "../inc/character.h"
#include "../inc/SDL_utils.h"

int main(int argc, char *argv[])
{
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	TTF_Font *font = nullptr;
	// SDL_Color color = {255, 0, 0, 255};
	// SDL_Surface *fpsTextSurface = nullptr;
	// SDL_Texture *fpsTextTextures[10];
	// SDL_Rect fpsRenderRect;

	int SDL_status = init_SDL(&renderer, &window, &font);

	if (SDL_status) {
		quit_SDL(renderer, window, font);
		return SDL_status;
	}

	int width = 0, height = 0, GAP[2] = {0, 0}, d = 0, x = 0, y = 0;
	double ratio = 0.0, RATIO = 0.0;

	SDL_GetWindowSize(window, &width, &height);
	ratio = (double)width / height;

	if (ratio > 16 / 9.0) {
		RATIO = height / 1080.0;
		GAP[0] = (width - RATIO * 1920) / 2;
	}
	else {
		RATIO = width / 1920.0;
		GAP[1] = (height - RATIO * 1080) / 2;
	}

	int nbBlocks = 5, nb_boosts = 1;

	Block blocks[] = {
		{0, 0, 1920, 100},
		{0, 0, 100, 1080},
		{1820, 0, 100, 1080},
		{0, 980, 1920, 100},
		{200, 500, 500, 100},
	};

	Block_setup(nbBlocks, blocks, GAP, RATIO);

	Boost boosts[] = {
		{800, 400}
	};

	End start = {200, 200};
	End end = {1700, 200};

	End_setup(&start, &end, GAP, RATIO);

	// initialisation of character
	Character character(&start, GAP, RATIO, font, renderer);

	// char text[1];

	// for (int i = 0; i < 10; i++)
	// {
	// 	text[0] = 48 + i;
	// 	fpsTextSurface = TTF_RenderText_Solid(font, text, color);
	// 	fpsTextTextures[i] = SDL_CreateTextureFromSurface(renderer, fpsTextSurface);
	// }

	// SDL_FreeSurface(fpsTextSurface);

	SDL_Event event;
	long startTime;
	int running = 1;//, textWidth = 0, textHeight = 0, fps = 60, fpsRefresh = 0;

	// main loop
	while (running) {
		startTime = SDL_GetTicks64();

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT)
				running = 0;

			// keys detection
			if (event.type == SDL_KEYDOWN) {
				SDL_Keycode key = event.key.keysym.sym;
				if (key == SDLK_ESCAPE)
					running = 0;

				if (key == SDLK_z)
					character.grab = 1;

				if (key == SDLK_d && d == 0)
					d = 1;

				if (key == SDLK_UP)
					y = -1;

				if (key == SDLK_DOWN)
					y = 1;

				if (key == SDLK_LEFT) {
					x = -1;
					if (character.collideY == 1)
						character.walk = -1;
				}

				if (key == SDLK_RIGHT) {
					x = 1;
					if (character.collideY == 1)
						character.walk = 1;
				}
			}
			if (event.type == SDL_KEYUP) {
				SDL_Keycode key = event.key.keysym.sym;

				if (key == SDLK_z)
					character.grab = 0;

				if (key == SDLK_d)
					d = 0;

				if (key == SDLK_UP || key == SDLK_DOWN)
					y = 0;

				if ((key == SDLK_LEFT && x == -1) || (key == SDLK_RIGHT && x == 1))
				{
					x = 0;
					character.walk = 0;
				}
			}
		}

		if (d == 1 && (x != 0 || y != 0)) {
			character.dash(x, y);
			d = 2;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (int i = 0; i < nbBlocks; i++)
			blocks[i].render(renderer);

		// for (int i = 0; i < nbBlocks; i++)
		// 	boosts[i].render(renderer);

		start.render(renderer);
		end.render(renderer);

		character.render(nbBlocks, blocks, nb_boosts, boosts);

		// if (SDL_GetTicks64() > fpsRefresh)
		// {
		// 	SDL_QueryTexture(fpsTextTextures[fps / 10], NULL, NULL, &textWidth, &textHeight);
		// 	fpsRenderRect = {0, 0, textWidth, textHeight};
		// 	SDL_RenderCopy(renderer, fpsTextTextures[fps / 10], NULL, &fpsRenderRect);
		// 	fpsRenderRect = {textWidth, 0, textWidth, textHeight};
		// 	SDL_RenderCopy(renderer, fpsTextTextures[fps % 10], NULL, &fpsRenderRect);
		// 	fpsRefresh = SDL_GetTicks64() + 16;
		// }

		SDL_RenderPresent(renderer);

		SDL_Delay(16 - (SDL_GetTicks64() - startTime));
		//printf("%ld\n", 1000 / (SDL_GetTicks64() - startTime));
					   // fpsRefresh--;
					   // fps = 1000 / (SDL_GetTicks64() - startTime);
	}

	// for (int i = 0; i < 10; i++)
	// 	SDL_DestroyTexture(fpsTextTextures[i]);

	quit_SDL(renderer, window, font);
	return 0;
}
