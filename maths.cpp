#include "maths.hpp"
#include "corps.hpp"
#include "vector.hpp"
#include <cmath>
#include <complex>
#include <vector>

Vector addition_entre_vecteur(Vector un, Vector deux) {
    Vector base = un;
    base.x += deux.x;
    base.y += deux.y;
    return base;
}

Vector soustration_entre_vecteur(Vector un, Vector deux){
    Vector base = Vector();
    base.x = deux.x - un.x;
    base.y = deux.y - un.x;

    return base;
}

Vector mutliplcation_vecteur_valeur(Vector a, double valeur){
    Vector base = a;
    base.x *= valeur;
    base.y *= valeur;
    return base;
}

Vector somme_vecteur(Tableau_de_Corps &a) {
    Vector base = Vector();
    for (int i = 0; i < a.nb_corps; i++) {
        base = addition_entre_vecteur(base, a.tab[i]->acceleration);
    }
    return base;
}

Vector normalisation(Vector a){
    Vector base = Vector();
    double norme = std::sqrt((a.x)*(a.x) + (a.y)*(a.y));
    base.x /= norme;
    base.y /= norme;

    return base;
}

double distance_entre_vecteur(Vector un, Vector deux) {
    double new_x = deux.x - un.x;
    double new_y = deux.y - un.y;
    return std::sqrt(new_x * new_x + new_y * new_y);
}

Vector calcule_vecteur_champs_gravitionnel(Corps &actuelle, Tableau_de_Corps &tous_les_corps, const double g){
    Vector acceleration = Vector();
    for (int i = 0; i < tous_les_corps.nb_corps; i++){

    }

    return acceleration;
}
