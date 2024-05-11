#ifndef CG2324_VECTOR3_H
#define CG2324_VECTOR3_H


struct Point3;

class Vector3
{
public:
    float x{}, y{}, z{};

public:
    Vector3() : x(0), y(0), z(0) {}

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    explicit Vector3(const Point3 &p);

    Vector3(const Point3 &p1, const Point3 &p2);

    explicit Vector3(tinyxml2::XMLElement *vectorElement);

    Vector3 operator+(const Vector3 &vector) const;

    Vector3 operator+=(const Vector3 &vector);

    Vector3 operator*(float scalar) const;

    Vector3 normalize();

    Vector3 cross(Vector3 vector3);

    static Vector3 normalize(Vector3 v);

    static Vector3 cross(Vector3 v1, Vector3 v2);
};


#endif //CG2324_VECTOR3_H
