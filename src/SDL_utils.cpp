// #include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>

#include "../inc/SDL_utils.hpp"
#include <SDL2/SDL_video.h>

int init_SDL(SDL_Renderer **renderer, SDL_Window **window, TTF_Font **font) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() != 0) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		return 1;
	}

	*font = TTF_OpenFont("/home/gregoiremarion/Dev/dash/assets/fonts/OpenSans-ExtraBold.ttf", 20);
	if (font == NULL) {
		SDL_Log("Erreur chargement police : %s", TTF_GetError());
		return 1;
	}

	*window = SDL_CreateWindow("Dash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == NULL) {
		fprintf(stderr, "Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
		return 1;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "Erreur lors de la création du renderer: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}

void quit_SDL(SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_CloseFont(font);
	TTF_Quit();
}
