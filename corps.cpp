#include "corps.hpp"
#include "maths.hpp"
#include "vector.hpp"

void Corps::update_corps(const double dt, const Tableau_de_Corps &tous_les_corps, const double g){
    Vector ancienne_acceleration = this->acceleration;
    position = calcule_position_methode_verlet(*this, dt);
    acceleration = calcule_vecteur_champs_gravitionnel(*this, tous_les_corps, g);
    speed = calcule_vitesse_methode_verlet(ancienne_acceleration, *this, dt);
}

void Tableau_de_Corps::maj_tab_apres_fusion(int i, int j, Corps *corps_fusionne){
    Corps *tmp_corps_1 = this->tab[i];
    Corps *tmp_corps_2 = this->tab[j];

    this->tab[i] = corps_fusionne;

    if (j != nb_corps - 1)
        this->tab[j] = this->tab[nb_corps - 1];

    tab[nb_corps - 1] = nullptr;

    delete tmp_corps_1;
    delete tmp_corps_2;
    nb_corps--;
}

void Corps::choisis_couleur(double mass_max) {
    double ratio = mass / mass_max;
    if (ratio > 1.0) ratio = 1.0;

    this->couleur->r = (int)(255 * ratio);
    this->couleur->g = 0;
    this->couleur->b = (int)(255 * (1.0 - ratio));
}
