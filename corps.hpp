#ifndef CORPS
#define CORPS

class Vector{
public:
    float x;
    float y;
};

class Corps{
public:
    Vector speed;
    Vector acceleration;
    Vector position;
    float mass;
};

#endif
