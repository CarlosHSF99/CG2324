#ifndef CG2324_CONE_H
#define CG2324_CONE_H


#include "generator/model.h"

class Cone : public Model
{
public:
    Cone(double radius, double height, int slices, int stacks);
};


#endif //CG2324_CONE_H
