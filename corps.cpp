#include "corps.hpp"
#include "maths.hpp"

void Corps::update_corps(double dt, const Tableau_de_Corps &tous_les_corps, const double g){
    acceleration = calcule_vecteur_champs_gravitionnel(*this ,tous_les_corps, g);
    speed = addition_entre_vecteur(speed, multiplication_vecteur_valeur(acceleration, dt));
    position = addition_entre_vecteur(position, multiplication_vecteur_valeur(speed, dt));
}
