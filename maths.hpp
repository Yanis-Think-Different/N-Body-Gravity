#ifndef MATHS
#define MATHS

#include "vector.hpp"
#include "corps.hpp"

Vector addition_entre_vecteur(Vector un, Vector deux);
Vector multiplication_vecteur_valeur(Vector a, double valeur);
Vector somme_vecteur(Tableau_de_Corps &a);
Vector normalisation(Vector a);
Vector soustration_entre_vecteur(Vector un, Vector deux);
double distance_entre_vecteur(Vector un, Vector deux);
Vector calcule_vecteur_champs_gravitionnel(Corps& actuelle, Tableau_de_Corps& tous_les_corps, const double g);

#endif
