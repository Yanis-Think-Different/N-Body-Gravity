// affichage.hpp
#ifndef AFFICHAGE
#define AFFICHAGE

#include <SDL2/SDL.h>
#include "corps.hpp"

void dessine_cercle(SDL_Renderer *renderer, Corps *actuelle);
void dessine_trajectoires(SDL_Renderer *renderer, const Tableau_de_Corps &tous_les_corps);
void choisis_couleur(Corps *corps, double mass_max);

#endif
