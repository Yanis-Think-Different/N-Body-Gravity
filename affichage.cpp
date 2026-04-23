#include "affichage.hpp"
#include <SDL2/SDL.h>

void dessine_cercle(SDL_Renderer *renderer, int cx, int cy, int r) {
    double x = 0;
    double y = -r;
    double p = -r;

    while (x < -y) {
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);

        if (p > 0) {
            y += 1;
            p += 2 * (x + y) + 1;
        } else {
            p += 2 * x + 1;
        }
        x++;
    }
}

void dessine_tous_les_corps(SDL_Renderer *renderer, const Tableau_de_Corps &tous_les_corps) {
    double mass_max = 1.0;
    for (int i = 0; i < tous_les_corps.nb_corps; i++) {
        if (tous_les_corps.tab[i]->mass > mass_max)
            mass_max = tous_les_corps.tab[i]->mass;
    }

    for (int i = 0; i < tous_les_corps.nb_corps; i++) {
        Corps *c = tous_les_corps.tab[i];
        dessine_cercle(renderer, c->position.x, c->position.y, c->rayon);
    }
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
