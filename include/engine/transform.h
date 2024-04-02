#ifndef CG2324_TRANSFORM_H
#define CG2324_TRANSFORM_H


#include "utils/vector3.h"

class Transform
{
public:
    virtual ~Transform() = default;

    virtual void apply() const noexcept = 0;
};

class Translate : public Transform
{
private:
    Vector3 vector;

public:
    explicit Translate(Vector3 vector) : vector(vector) {}

    Translate(float x, float y, float z) : vector(x, y, z) {}

    void apply() const noexcept override;
};

class Rotate : public Transform
{
private:
    float angle;
    Vector3 vector;

public:
    Rotate(float angle, Vector3 vector) : angle(angle), vector(vector) {}

    Rotate(float angle, float x, float y, float z) : angle(angle), vector(x, y, z) {}

    void apply() const noexcept override;
};

class Scale : public Transform
{
private:
    float factorX, factorY, factorZ;

public:
    Scale(float x, float y, float z) : factorX(x), factorY(y), factorZ(z) {}

    void apply() const noexcept override;
};


#endif //CG2324_TRANSFORM_H
