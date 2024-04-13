#ifndef CG2324_POINT3_H
#define CG2324_POINT3_H


#include <ostream>
#include "vector3.h"

struct Point3
{
    float x, y, z;

    Point3() : x(0), y(0), z(0) {}

    Point3(float x, float y, float z);

    Point3 operator+(const Vector3 &vector) const;

    Point3 operator+(const std::tuple<float, float, float> &vector) const;

    friend std::ostream &operator<<(std::ostream &os, const Point3 &point);

    Point3 &operator=(const Point3 &other) noexcept;
};


#endif //CG2324_POINT3_H
