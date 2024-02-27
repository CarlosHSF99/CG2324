#ifndef CG2324_VECTOR3_H
#define CG2324_VECTOR3_H


class Vector3
{
public:
    const float x, y, z;

public:
    Vector3() : x(0), y(0), z(0) {}

    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3 &vector) const;

    Vector3 operator+(const std::tuple<float, float, float> &vector) const;

    Vector3 operator*(float scalar) const;
};


#endif //CG2324_VECTOR3_H
