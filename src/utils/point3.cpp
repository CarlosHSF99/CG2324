#include <iostream>
#include "utils/vector3.h"
#include "utils/point3.h"

using std::ostream, std::tuple;

Point3::Point3(float x, float y, float z) : x(x), y(y), z(z) {}

Point3 Point3::operator+(const Vector3 &v) const
{
    return {x + v.x, y + v.y, z + v.z};
}

Point3 Point3::operator+(const tuple<float, float, float> &v) const
{
    auto [vx, vy, vz] = v;
    return {x + vx, y + vy, z + vz};
}

ostream &operator<<(ostream &os, const Point3 &point)
{
    os << '(' << point.x << ", " << point.y << ", " << point.z << ')';
    return os;
}

Point3 &Point3::operator=(Point3 const &other) noexcept
{
    if (this != &other) {
        std::destroy_at(this);
        std::construct_at(this, other);
    }
    return *this;
}
