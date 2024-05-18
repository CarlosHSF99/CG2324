#ifndef CG2324_POINT3_H
#define CG2324_POINT3_H


#include <ostream>
#include "deps/tinyxml2.h"

class Vector3;

struct Point3
{
    float x{}, y{}, z{};

    Point3() : x(0), y(0), z(0) {}

    Point3(double x, double y, double z) : x((float) x), y((float) y), z((float) z) {}

    explicit Point3(tinyxml2::XMLElement *pointElement);

    Point3 operator+(const Vector3 &vector) const;

    Point3 operator+=(const Vector3 &vector);

    friend std::ostream &operator<<(std::ostream &os, const Point3 &point);

    Point3 &operator=(const Point3 &other) noexcept;
};


#endif //CG2324_POINT3_H
