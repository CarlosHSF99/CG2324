#include <tuple>
#include "utils/vector3.h"
#include "utils/point3.h"

using std::tuple;

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3(const Point3 &p) : x(p.x), y(p.y), z(p.z) {}

Vector3::Vector3(const Point3 &p1, const Point3 &p2) : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return {x + v.x, y + v.y, z + v.z};
}

Vector3 Vector3::operator+=(const Vector3 &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3 Vector3::operator+(const tuple<float, float, float> &v) const
{
    auto [vx, vy, vz] = v;
    return {x + vx, y + vy, z + vz};
}

Vector3 Vector3::operator*(float scalar) const
{
    return {x * scalar, y * scalar, z * scalar};
}
