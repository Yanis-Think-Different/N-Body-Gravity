#include "corps.hpp"
#include "maths.hpp"
#include "vector.hpp"

void Corps::update_corps(const double dt, const Tableau_de_Corps &tous_les_corps, const double g){
    Vector ancienne_acceleration = this->acceleration;
    position = calcule_position_methode_verlet(*this, dt);
    acceleration = calcule_vecteur_champs_gravitionnel(*this, tous_les_corps, g);
    speed = calcule_vitesse_methode_verlet(ancienne_acceleration, *this, dt);
}
