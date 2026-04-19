#ifndef MATHS
#define MATHS

#include "vector.hpp"
#include "corps.hpp"

Vector addition_entre_vecteur(Vector un, Vector deux);
Vector mutliplcation_vecteur_valeur(Vector &a, double valeur);
Vector somme_vecteur(Tableau_de_Corps &a);
Vector force_subit_par_le_corps(Tableau_de_Corps &tous_les_corps);
Vector normalisation(Vector a);
Vector soustration_entre_vecteur(Vector un, Vector deux);
double distance_entre_vecteur();

#endif
