#include "affichage.hpp"
#include "corps.hpp"
#include <SDL2/SDL.h>

void dessine_cercle(SDL_Renderer *renderer, Corps *actuelle) {
    double x = 0;
    double y = -actuelle->rayon;
    double p = -actuelle->rayon;

    while (x < -y) {
        SDL_RenderDrawLine(renderer, actuelle->position.x - x, actuelle->position.y + y, actuelle->position.x + x, actuelle->position.y + y);
        SDL_RenderDrawLine(renderer, actuelle->position.x - x, actuelle->position.y - y, actuelle->position.x + x, actuelle->position.y - y);
        SDL_RenderDrawLine(renderer, actuelle->position.x - y, actuelle->position.y + x, actuelle->position.x + y, actuelle->position.y + x);
        SDL_RenderDrawLine(renderer, actuelle->position.x - y, actuelle->position.y - x, actuelle->position.x + y, actuelle->position.y - x);

        if (p > 0) {
            y += 1;
            p += 2 * (x + y) + 1;
        } else {
            p += 2 * x + 1;
        }
        x++;
    }
}

void choisis_couleur(Corps *corps, double mass_max){
    double ratio = corps->mass / mass_max;
    if (ratio > 1.0) ratio = 1.0;

    corps->couleur->r = (int)(255 * ratio);
    corps->couleur->g = 0;
    corps->couleur->b = (int)(255 * (1.0 - ratio));
}

void dessine_trajectoires(SDL_Renderer *renderer, const Tableau_de_Corps &tous_les_corps) {
    for (int i = 0; i < tous_les_corps.nb_corps; i++) {
        Corps *c = tous_les_corps.tab[i];
        if (c->historique_positions.size() < 2)
            continue;

        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);

        for (size_t j = 1; j < c->historique_positions.size(); j++) {
            SDL_RenderDrawLine(renderer,
                c->historique_positions[j-1].x,
                c->historique_positions[j-1].y,
                c->historique_positions[j].x,
                c->historique_positions[j].y
            );
        }
    }
}
