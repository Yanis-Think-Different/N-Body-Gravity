#include "corps.hpp"
#include "maths.hpp"
#include "vector.hpp"

void Corps::update_corps(const double dt, const Tableau_de_Corps &tous_les_corps, const double g, double largeur, double hauteur){
    Vector ancienne_acceleration = this->acceleration;
    position = calcule_position_methode_verlet(*this, dt);
    acceleration = calcule_vecteur_champs_gravitionnel(*this, tous_les_corps, g);
    speed = calcule_vitesse_methode_verlet(ancienne_acceleration, *this, dt);

    historique_positions.push_back(position);
    if (historique_positions.size() > 100) {
        historique_positions.pop_front();
    }

    // rebond bord
    if (position.x - rayon < 0) {
        position.x = rayon;
        speed.x *= -0.8; // Le 0.8 permet de perdre un peu d'énergie au choc
    } else if (position.x + rayon > 1280) {
        position.x = 1280 - rayon;
        speed.x *= -0.8;
    }

    if (position.y - rayon < 0) {
        position.y = rayon;
        speed.y *= -0.1;
    } else if (position.y + rayon > 720) {
        position.y = 720 - rayon;
        speed.y *= -0.8;
    }

    /* TOROIDAL
    if (position.x < 0) position.x = largeur;
    if (position.x > largeur) position.x = 0;
    if (position.y < 0) position.y = hauteur;
    if (position.y > hauteur) position.y = 0;
    */
}

Tableau_de_Corps::Tableau_de_Corps(int t) {
    taille = t;
    nb_corps = 0;
    mass_max = 0;

    tab = new Corps * [taille];

    for (int i = 0; i < taille; i++) {
        tab[i] = nullptr;
    }
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

Corps::Corps(double m, double r, Vector s, Vector p, Vector a) {
    mass = m;
    rayon = r;
    speed = s;
    position = p;
    acceleration = a;
    couleur = new Color();
    couleur->r = 255;
    couleur->g = 255;
    couleur->b = 255;
}

Corps::Corps(double m, double r, Vector s, Vector p) {
    mass = m;
    rayon = r;
    speed = s;
    position = p;
    acceleration = Vector();
    couleur = new Color();
    couleur->r = 255;
    couleur->g = 255;
    couleur->b = 255;
}
