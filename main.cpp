#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <random>
#include "affichage.hpp"
#include "corps.hpp"
#include "maths.hpp"
#include "vector.hpp"

#define LARGEUR 1280
#define HAUTEUR 720
#define NB_CORPS 40

// Constante Physique
const double GRAVITATIONAL_CONSTANT = 1000.0;

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());

	SDL_Window* window = NULL;
	SDL_Renderer* rendu = NULL;
	SDL_Event ev;
	double dt = 0.016;

	std::uniform_real_distribution<double> rand_mass(0.0, 100.0);
	std::uniform_real_distribution<double> rand_rayon(1.0, 2.0);
	std::uniform_real_distribution<double> rand_vector(-5.0, 5.0);
	std::uniform_real_distribution<double> rand_posistion_x(100.0, 1000.0);
	std::uniform_real_distribution<double> rand_posistion_y(100.0, 650.0);

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

	Tableau_de_Corps liste_corps = Tableau_de_Corps(NB_CORPS);

	for (int i = 0; i < NB_CORPS; i++){
	    Vector speed = Vector(rand_vector(gen), rand_vector(gen));
		Vector position = Vector(rand_posistion_x(gen), rand_posistion_y(gen));
		double mass = rand_mass(gen);
		double rayon = rand_rayon(gen);

        liste_corps.tab[i] = new Corps(mass, rayon, speed, position, Vector());
        liste_corps.nb_corps++;

        if (liste_corps.mass_max < mass)
            liste_corps.mass_max = mass;
	}

	for (int i = 0; i < liste_corps.nb_corps; i++){
        choisis_couleur(liste_corps.tab[i], liste_corps.mass_max);
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
        ////////
        for (int i = 0; i < liste_corps.nb_corps; i++){
            for (int j = 0; j < liste_corps.nb_corps; j++){
                if (i == j)
                    continue;
                else if (collide_corps(liste_corps.tab[i], liste_corps.tab[j])){
                    Corps *new_corps = fusion_deux_corps(*liste_corps.tab[i], *liste_corps.tab[j]);
                    if (new_corps->mass > liste_corps.mass_max) liste_corps.mass_max = new_corps->mass;
                    choisis_couleur(new_corps, liste_corps.mass_max);
                    liste_corps.maj_tab_apres_fusion(i, j, new_corps);
                }
                else continue;
            }
        }

        for (int i = 0; i < liste_corps.nb_corps; i++)
            liste_corps.tab[i]->update_corps(dt, liste_corps, (double)GRAVITATIONAL_CONSTANT, (double)LARGEUR, (double)HAUTEUR);

        ////////

        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        SDL_RenderClear(rendu);
        //dessine_trajectoires(rendu, liste_corps);

        for (int i = 0; i < liste_corps.nb_corps; i++) {
            SDL_SetRenderDrawColor(rendu, liste_corps.tab[i]->couleur->r,
                                          liste_corps.tab[i]->couleur->g,
                                          liste_corps.tab[i]->couleur->b, 255);
            dessine_cercle(rendu, liste_corps.tab[i]);
        }

        SDL_RenderPresent(rendu);
    }

	// Fin
	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
