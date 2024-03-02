#ifndef CG2324_CONE_H
#define CG2324_CONE_H


#include "model.h"

class Cone : public Model
{
public:
    Cone(float radius, float height, int slices, int stacks);
};


#endif //CG2324_CONE_H
