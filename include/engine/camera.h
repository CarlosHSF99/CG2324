#ifndef CG2324_CAMERA_H
#define CG2324_CAMERA_H


#include "utils/point3.h"
#include "utils/vector3.h"

class Camera
{
private:
    Point3 position;
    Point3 lookAt;
    Vector3 up;
    float fov{}, near{}, far{};
    float pitch{}, yaw{};
    float radius{};

public:
    Camera() = default;

    Camera(const Point3 &position, const Point3 &lookAt, const Vector3 &up, float fov, float near, float far);

    void place();

    void reactKey(unsigned char key, int x, int y);

    void setPerspective(int w, int h) const;
};


#endif //CG2324_CAMERA_H
