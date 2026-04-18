#ifndef CORPS
#define CORPS

class Vector{
public:
    double x;
    double y;
};

class Corps{
public:
    Vector speed;
    Vector acceleration;
    Vector position;
    double mass;
    double rayon;

    Vector calcule_champs_gravite(const double g, const Corps *x);
};

#endif
