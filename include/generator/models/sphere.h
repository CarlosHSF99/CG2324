#ifndef CG2324_SPHERE_H
#define CG2324_SPHERE_H


#include "model.h"

class Sphere : public Model
{
public:
    Sphere(double radius, int slices, int stacks);

    Sphere(double radius, int slices, int stacks, const std::string &heightMap, double heightScale);

private:
    void buildSphere(int slices, int stacks, const std::vector<Vertex> &grid);
};


#endif //CG2324_SPHERE_H
