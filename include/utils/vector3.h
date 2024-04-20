#ifndef CG2324_VECTOR3_H
#define CG2324_VECTOR3_H

#include <tuple>

struct Point3;

class Vector3
{
public:
    float x, y, z;

public:
    Vector3() : x(0), y(0), z(0) {}

    Vector3(float x, float y, float z);

    explicit Vector3(const Point3 &p);

    Vector3(const Point3 &p1, const Point3 &p2);

    Vector3 operator+(const Vector3 &vector) const;

    Vector3 operator+=(const Vector3 &vector);

    Vector3 operator+(const std::tuple<float, float, float> &vector) const;

    Vector3 operator*(float scalar) const;
};


#endif //CG2324_VECTOR3_H
