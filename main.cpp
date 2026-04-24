#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <random>
#include "affichage.hpp"
#include "corps.hpp"
#include "maths.hpp"
#include "vector.hpp"

#define LARGEUR 1920
#define HAUTEUR 1080
#define NB_CORPS 5000

// Constante Physique
const double GRAVITATIONAL_CONSTANT = 100.0;

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());

	SDL_Window* window = NULL;
	SDL_Renderer* rendu = NULL;
	SDL_Event ev;
	double dt = 0.0008;

	std::uniform_real_distribution<double> rand_mass(0.0, 100.0);
	std::uniform_real_distribution<double> rand_rayon(1.0, 2.0);
	std::uniform_real_distribution<double> rand_vector(-5.0, 5.0);
	std::uniform_real_distribution<double> rand_posistion_x((double) 0, (double)LARGEUR);
	std::uniform_real_distribution<double> rand_posistion_y((double) 0, (double)HAUTEUR);

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

	//------------------------------------------------------------Pour du random pure et dure---------------------------------------------------------------//

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


	//------------------------------------------------------------Imitation du systeme solaire---------------------------------------------------------------//
	/*
	// Soleil
    liste_corps.tab[0] = new Corps(100000.0, 30.0, Vector(0.0, 0.0), Vector(960.0, 540.0), Vector());
    liste_corps.nb_corps++;

    // Mercure - distance 150
    liste_corps.tab[1] = new Corps(10.0, 5.0, Vector(577.0, 0.0), Vector(960.0, 390.0), Vector());
    liste_corps.nb_corps++;

    // Venus - distance 280
    liste_corps.tab[2] = new Corps(20.0, 8.0, Vector(423.0, 0.0), Vector(960.0, 260.0), Vector());
    liste_corps.nb_corps++;

    // Terre - distance 400
    liste_corps.tab[3] = new Corps(30.0, 9.0, Vector(354.0, 0.0), Vector(960.0, 140.0), Vector());
    liste_corps.nb_corps++;

    // Mars - distance 550
    liste_corps.tab[4] = new Corps(15.0, 7.0, Vector(302.0, 0.0), Vector(960.0, -10.0), Vector());
    liste_corps.nb_corps++;

    liste_corps.mass_max = 100000.0;

    // Couleurs
    liste_corps.tab[0]->couleur->r = 255; liste_corps.tab[0]->couleur->g = 255; liste_corps.tab[0]->couleur->b = 0;   // Soleil jaune
    liste_corps.tab[1]->couleur->r = 169; liste_corps.tab[1]->couleur->g = 169; liste_corps.tab[1]->couleur->b = 169; // Mercure gris
    liste_corps.tab[2]->couleur->r = 255; liste_corps.tab[2]->couleur->g = 140; liste_corps.tab[2]->couleur->b = 0;   // Venus orange
    liste_corps.tab[3]->couleur->r = 0;   liste_corps.tab[3]->couleur->g = 100; liste_corps.tab[3]->couleur->b = 255; // Terre bleu
    liste_corps.tab[4]->couleur->r = 188; liste_corps.tab[4]->couleur->g = 74;  liste_corps.tab[4]->couleur->b = 60;  // Mars rouge

    liste_corps.mass_max = 100000.0;

    for (int i = 0; i < liste_corps.nb_corps; i++) {
        liste_corps.tab[i]->acceleration = calcule_vecteur_champs_gravitionnel(
            *liste_corps.tab[i], liste_corps, GRAVITATIONAL_CONSTANT
        );
    }
    */

	// Boucle
	while (running) {
        while (SDL_PollEvent(&ev) != 0) {
            switch (ev.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_q) {
                        running = false;
                    }
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
	liste_corps.nettoyer();
	SDL_DestroyRenderer(rendu);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
