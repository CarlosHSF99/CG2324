#include <cmath>
#include "deps/tinyxml2.h"
#include "utils/vector3.h"
#include "utils/point3.h"

using std::ostream;
using namespace tinyxml2;

Point3::Point3(XMLElement *vectorElement)
{
    vectorElement->QueryFloatAttribute("x", &x);
    vectorElement->QueryFloatAttribute("y", &y);
    vectorElement->QueryFloatAttribute("z", &z);
}

Point3 Point3::operator+(const Vector3 &v) const
{
    return {x + v.x, y + v.y, z + v.z};
}

Point3 Point3::operator+=(const Vector3 &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
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

Point3 Point3::polar(double radius, double alpha, double beta)
{
    return {radius * cos(beta) * sin(alpha), radius * sin(beta), radius * cos(beta) * cos(alpha)};
}
