#ifndef CG2324_VECTOR3_H
#define CG2324_VECTOR3_H


#include <ostream>
#include "deps/tinyxml2.h"

struct Point3;

struct Vector3
{
    float x{}, y{}, z{};

    Vector3() : x(0), y(0), z(0) {}

    Vector3(double x, double y, double z) : x((float) x), y((float) y), z((float) z) {}

    explicit Vector3(const Point3 &p);

    Vector3(const Point3 &p1, const Point3 &p2);

    explicit Vector3(tinyxml2::XMLElement *vectorElement);

    Vector3 operator+(const Vector3 &vector) const;

    Vector3 operator+=(const Vector3 &vector);

    Vector3 operator*(double scalar) const;

    Vector3 normalize();

    Vector3 cross(Vector3 vector3);

    static Vector3 polar(double radius, double alpha, double beta);

    static Vector3 normalize(Vector3 v);

    static Vector3 cross(Vector3 v1, Vector3 v2);

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &vector);
};


#endif //CG2324_VECTOR3_H
