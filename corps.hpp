#ifndef CORPS
#define CORPS

#include "vector.hpp"
#include <deque>

class Corps;
class Tableau_de_Corps;

class Color{
public:
    int r;
    int g;
    int b;
};

class Corps{
public:
    Vector speed;
    Vector acceleration;
    Vector position;
    Color *couleur;
    double mass;
    double rayon;
    std::deque<Vector> historique_positions;

    Corps(double m, double r, Vector s, Vector p){
        mass = m;
        rayon = r;
        speed = s;
        position = p;
        acceleration = Vector();
    }
    Corps(double m, double r, Vector s, Vector p, Vector a){
        mass = m;
        rayon = r;
        speed = s;
        position = p;
        acceleration = a;
    }

    void update_corps(double dt, const Tableau_de_Corps &tous_les_corps, const double g);
    void choisis_couleur(double mass_max);
};

class Tableau_de_Corps{
public:
    Corps **tab;
    int taille;
    int nb_corps;

    Tableau_de_Corps(int t){
        taille = t;
        nb_corps = 0;

        tab = new Corps*[taille];

        for (int i =0; i < taille; i++){
            tab[i] = nullptr;
        }
    }

    void maj_tab_apres_fusion(int i, int j, Corps *corps_fusionne);
};



#endif
