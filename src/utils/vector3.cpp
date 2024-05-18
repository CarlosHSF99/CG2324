#include <cmath>
#include "deps/tinyxml2.h"
#include "utils/vector3.h"
#include "utils/point3.h"

using std::tuple;
using namespace tinyxml2;

Vector3::Vector3(const Point3 &p) : x(p.x), y(p.y), z(p.z) {}

Vector3::Vector3(const Point3 &p1, const Point3 &p2)
        : x(p2.x - p1.x), y(p2.y - p1.y), z(p2.z - p1.z) {}

Vector3::Vector3(XMLElement *vectorElement)
{
    vectorElement->QueryFloatAttribute("x", &x);
    vectorElement->QueryFloatAttribute("y", &y);
    vectorElement->QueryFloatAttribute("z", &z);
}

Vector3 Vector3::polar(double radius, double alpha, double beta)
{
    return {radius * cos(beta) * sin(alpha), radius * sin(beta), radius * cos(beta) * cos(alpha)};
}

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

Vector3 Vector3::operator*(double scalar) const
{
    return {x * scalar, y * scalar, z * scalar};
}

Vector3 Vector3::normalize()
{
    float d = std::sqrt(x * x + y * y + z * z);
    if (d != 0) {
        x = x / d;
        y = y / d;
        z = z / d;
    }
    return *this;
}

Vector3 Vector3::cross(Vector3 v)
{
    return *this = {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
}

Vector3 Vector3::normalize(Vector3 v)
{
    float magnitude = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return {v.x / magnitude, v.y / magnitude, v.z / magnitude};
}

Vector3 Vector3::cross(Vector3 v1, Vector3 v2)
{
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

std::ostream &operator<<(std::ostream &os, const Vector3 &vector)
{
    os << '(' << vector.x << ", " << vector.y << ", " << vector.z << ')';
    return os;
}
