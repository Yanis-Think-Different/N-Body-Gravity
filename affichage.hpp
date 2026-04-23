// affichage.hpp
#ifndef AFFICHAGE
#define AFFICHAGE

#include <SDL2/SDL.h>
#include "corps.hpp"

void dessine_cercle(SDL_Renderer *renderer, int cx, int cy, int r);
void dessine_tous_les_corps(SDL_Renderer *renderer, const Tableau_de_Corps &tous_les_corps);
void dessine_trajectoires(SDL_Renderer *renderer, const Tableau_de_Corps &tous_les_corps);

#endif
