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
    ~Corps() { delete couleur; }

    Corps(double m, double r, Vector s, Vector p);
    Corps(double m, double r, Vector s, Vector p, Vector a);
    void update_corps(const double dt, const Tableau_de_Corps &tous_les_corps, const double g, double largeur, double hauteur);
};

class Tableau_de_Corps{
public:
    Corps **tab;
    int taille;
    int nb_corps;
    double mass_max;

    Tableau_de_Corps(int t);
    void maj_tab_apres_fusion(int i, int j, Corps *corps_fusionne);
    void nettoyer();
};



#endif
