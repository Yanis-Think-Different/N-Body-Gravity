#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>

#define LARGEUR 1280
#define HAUTEUR 720
#define INCREMENT_PLACE 5

// Constante Physique
const double GRAVITATIONAL_CONSTANT = 6.674e-11;

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));

	SDL_Window* window = NULL;
	SDL_Renderer* rendu = NULL;
	SDL_Event ev;

	int running = 1;

	// Initialisation
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Echec Initilisation : " << SDL_GetError() << std::endl;
		return 1;
	}

	window = SDL_CreateWindow("Simulateur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Pointeur windows est NULL" << std::endl;
		return 1;
	}

	rendu = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!rendu) {
		std::cerr << "Echec Initilisation : " << SDL_GetError() << std::endl;
		return 1;
	}

	// Boucle
	while (running) {
        while (SDL_PollEvent(&ev) != 0) {
            switch (ev.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderPresent(rendu);
    }

	// Fin
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
