#ifndef CG2324_VERTEX_H
#define CG2324_VERTEX_H


#include "point3.h"
#include "vector2.h"
#include "vector3.h"

struct Vertex
{
    Point3 position;
    Vector3 normal;
    Vector2 texCoords;

    Vertex() = default;

    Vertex(const Point3 &position, const Vector3 &normal, const Vector2 &texCoords) :
            position(position), normal(normal), texCoords(texCoords) {}

    Vertex &operator=(const Vertex &other) noexcept;
};


#endif //CG2324_VERTEX_H
