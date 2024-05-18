#ifndef CG2324_VERTEX_H
#define CG2324_VERTEX_H


#include "point3.h"
#include "vector3.h"

struct Vertex
{
    Point3 coords;
    Vector3 normal;

    Vertex() = default;

    Vertex(const Point3 &coords, const Vector3 &normal) :
            coords(coords), normal(normal) {}

    Vertex &operator=(const Vertex &other) noexcept;
};


#endif //CG2324_VERTEX_H
