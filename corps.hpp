#ifndef CORPS
#define CORPS

#include "vector.hpp"

class Corps;
class Tableau_de_Corps;

class Corps{
public:
    Vector speed;
    Vector acceleration;
    Vector position;
    double mass;
    double rayon;

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

    void update_corps(double dt, Tableau_de_Corps &tous_les_corps);
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
};

#endif
