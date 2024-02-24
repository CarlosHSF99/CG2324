#ifndef GENERATOR_SPHERE_H
#define GENERATOR_SPHERE_H


#include "model.h"

class Sphere : public Model
{
public:
    Sphere(double radius, int slices, int stacks);
};


#endif //GENERATOR_SPHERE_H
