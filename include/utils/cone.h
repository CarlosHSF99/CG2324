#ifndef GENERATOR_CONE_H
#define GENERATOR_CONE_H


#include "model.h"

class Cone : public Model
{
public:
    Cone(float radius, float height, int slices, int stacks);
};


#endif //GENERATOR_CONE_H
