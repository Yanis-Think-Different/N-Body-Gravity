#ifndef MATHS
#define MATHS

#include "vector.hpp"
#include "corps.hpp"

Vector addition_entre_vecteur(const Vector &un, const Vector &deux);
Vector multiplication_vecteur_valeur(const Vector &a, double valeur);
void normalisation(Vector &a);
Vector soustration_entre_vecteur(const Vector &un, const Vector &deux);
double distance_entre_vecteur(const Vector &un, const Vector &deux);
Vector calcule_vecteur_champs_gravitionnel(const Corps& actuelle, const Tableau_de_Corps& tous_les_corps, const double g);
Vector calcule_vitesse_methode_verlet(Vector ancienne_acceleration, const Corps &actuelle, const double dt);
Vector calcule_position_methode_verlet(const Corps &actuelle, const double dt);

#endif
