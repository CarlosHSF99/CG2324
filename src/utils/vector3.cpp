#include <tuple>
#include "utils/vector3.h"

using std::tuple;

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return {x + v.x, y + v.y, z + v.z};
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
