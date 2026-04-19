#ifndef VECTOR
#define VECTOR

class Vector {
public:
    double x;
    double y;

    Vector(){
        x = 0.0;
        y = 0.0;
    }
    Vector(double valeur_x, double valeur_y){
        x = valeur_x;
        y = valeur_y;
    }
};

#endif
