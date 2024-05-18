#ifndef CG2324_LIGHT_H
#define CG2324_LIGHT_H


#include <GL/glew.h>
#include <GL/glut.h>

#include "deps/tinyxml2.h"
#include "utils/vector3.h"

class Light
{
protected:
    GLenum id;

    Light();

public:
    virtual void place() const noexcept = 0;
};

class PointLight : public Light
{
private:
    Vector3 pos;

public:
    explicit PointLight(Vector3 position) : pos(position) {}

    explicit PointLight(tinyxml2::XMLElement *lightElement);

    void place() const noexcept override;
};

class DirectionalLight : public Light
{
private:
    Vector3 dir;

public:
    explicit DirectionalLight(Vector3 direction) : dir(direction) {}

    explicit DirectionalLight(tinyxml2::XMLElement *lightElement);

    void place() const noexcept override;
};

class SpotLight : public Light
{
private:
    Vector3 pos;
    Vector3 dir;
    float cutoff{};

public:
    explicit SpotLight(Vector3 position, Vector3 direction, float cutoff)
            : pos(position), dir(direction), cutoff(cutoff) {}

    explicit SpotLight(tinyxml2::XMLElement *lightElement);

    void place() const noexcept override;
};


#endif //CG2324_LIGHT_H
