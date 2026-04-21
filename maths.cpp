#include "maths.hpp"
#include "corps.hpp"
#include "vector.hpp"
#include <cmath>
#include <iostream>

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

Vector calcule_position_methode_verlet(const Corps &actuelle, const double dt){
    Vector position_verlet = Vector();
    Vector vitesse_upt = multiplication_vecteur_valeur(actuelle.speed, dt);
    Vector acceleration_upt = multiplication_vecteur_valeur(multiplication_vecteur_valeur(actuelle.acceleration, dt*dt), 0.5);
    position_verlet = addition_entre_vecteur(actuelle.position, addition_entre_vecteur(vitesse_upt, acceleration_upt));

    return position_verlet;
}

Vector calcule_vitesse_methode_verlet(Vector ancienne_acceleration, const Corps &actuelle, const double dt){
    Vector speed_verlet = Vector();
    Vector addition_entre_accelerations = addition_entre_vecteur(ancienne_acceleration, actuelle.acceleration);
    Vector acceleration_upt = multiplication_vecteur_valeur(multiplication_vecteur_valeur(addition_entre_accelerations, dt), 0.5);
    speed_verlet = addition_entre_vecteur(actuelle.speed, acceleration_upt);

    return speed_verlet;
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

bool collide_corps(const Corps *un, const Corps *deux){
    if (!un || !deux) {
        std::cerr << "Probleme Collide fonction" << std::endl;
        return false;
    }

    double dx = deux->position.x - un->position.x;
    double dy = deux->position.y - un->position.y;
    double distance_carree = dx*dx + dy*dy;
    double somme_rayons = un->rayon + deux->rayon;

    if (distance_carree < (somme_rayons * somme_rayons))
        return true;

    return false;
}

Corps *fusion_deux_corps(Corps &un, Corps &deux){
    double new_mass = un.mass + deux.mass;
    double new_rayon = std::sqrt(un.rayon*un.rayon + deux.rayon*deux.rayon);
    Vector new_position =   multiplication_vecteur_valeur(
                                addition_entre_vecteur(
                                    multiplication_vecteur_valeur(un.position, un.mass),
                                    multiplication_vecteur_valeur(deux.position, deux.mass)),
                                1/new_mass);
    Vector new_speed    =   multiplication_vecteur_valeur(
                                addition_entre_vecteur(
                                    multiplication_vecteur_valeur(un.speed, un.mass),
                                    multiplication_vecteur_valeur(deux.speed, deux.mass)),
                                1/new_mass);
    Vector new_acc      =   multiplication_vecteur_valeur(
                                addition_entre_vecteur(
                                    multiplication_vecteur_valeur(un.acceleration, un.mass),
                                    multiplication_vecteur_valeur(deux.acceleration, deux.mass)),
                                1/new_mass);

    Corps *nouveau_corps = new Corps(new_mass, new_rayon, new_speed, new_position, new_acc);

    return nouveau_corps;
}

void boucle_de_verification_fusion(Tableau_de_Corps &tous_les_corps){
    for (int i = 0; i < tous_les_corps.nb_corps; i++){
        for (int j = 0; j < tous_les_corps.nb_corps; j++){
            if (i == j)
                continue;
            else if (!collide_corps(tous_les_corps.tab[i], tous_les_corps.tab[j]))
                continue;
            else{
                Corps *new_corps = fusion_deux_corps(*tous_les_corps.tab[i], *tous_les_corps.tab[j]);
                tous_les_corps.maj_tab_apres_fusion(i, j, new_corps);
            }
        }
    }
}
