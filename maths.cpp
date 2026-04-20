#include "maths.hpp"
#include "corps.hpp"
#include "vector.hpp"
#include <cmath>

Vector addition_entre_vecteur(const Vector &un, const Vector &deux) {
    Vector base = un;
    base.x += deux.x;
    base.y += deux.y;
    return base;
}

Vector soustration_entre_vecteur(const Vector &un, const Vector &deux){
    Vector base = Vector();
    base.x = deux.x - un.x;
    base.y = deux.y - un.y;

    return base;
}

Vector multiplication_vecteur_valeur(const Vector &a, double valeur){
    Vector base = a;
    base.x *= valeur;
    base.y *= valeur;
    return base;
}

void normalisation(Vector &a){
    double norme = std::sqrt((a.x)*(a.x) + (a.y)*(a.y));
    a.x /= norme;
    a.y /= norme;
}

double distance_entre_vecteur(const Vector &un, const Vector &deux) {
    double new_x = deux.x - un.x;
    double new_y = deux.y - un.y;
    return std::sqrt(new_x * new_x + new_y * new_y);
}

Vector calcule_vecteur_champs_gravitionnel(const Corps &actuelle, const Tableau_de_Corps &tous_les_corps, const double g){
    Vector acceleration_corps_actuelle = Vector();
    for (int i = 0; i < tous_les_corps.nb_corps; i++){
        if (&actuelle == tous_les_corps.tab[i])
            continue;
        Vector position_normalise = Vector();
        position_normalise = soustration_entre_vecteur(actuelle.position, tous_les_corps.tab[i]->position);
        normalisation(position_normalise);

        double distance = distance_entre_vecteur(actuelle.position, tous_les_corps.tab[i]->position);

        Vector acceleration_corps_i = Vector();
        double valeur_acc = g * tous_les_corps.tab[i]->mass / (distance*distance);
        acceleration_corps_i = multiplication_vecteur_valeur(position_normalise, valeur_acc);
        acceleration_corps_actuelle = addition_entre_vecteur(acceleration_corps_actuelle, acceleration_corps_i);
    }

    return acceleration_corps_actuelle;
}
