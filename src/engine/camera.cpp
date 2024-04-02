#include <GL/glut.h>
#include <cmath>
#include "engine/camera.h"

Camera::Camera(const Point3 &position, const Point3 &lookAt, const Vector3 &up, float fov, float near, float far)
        : position(position), lookAt(lookAt), up(up), fov(fov), near(near), far(far)
{
    radius = sqrtf(powf(position.x - lookAt.x, 2) + powf(position.y - lookAt.y, 2) + powf(position.z - lookAt.z, 2));
    pitch = asinf((position.y - lookAt.y) / radius);
    yaw = atan2f(position.x - lookAt.x, position.z - lookAt.z);
}

void Camera::place()
{
    glLoadIdentity();

    position = {radius * cosf(pitch) * sinf(yaw),
                radius * sinf(pitch),
                radius * cosf(pitch) * cosf(yaw)};

    gluLookAt(position.x, position.y, position.z,
              lookAt.x, lookAt.y, lookAt.z,
              up.x, up.y, up.z);
}

void Camera::reactKey(unsigned char key, int x, int y)
{
    switch (key) {
        case 'w': // Slow pitch up
            pitch += 0.01;
            break;
        case 'W': // Fast pitch up
            pitch += 0.1;
            break;
        case 'a': // Slow yaw left
            yaw -= 0.01;
            break;
        case 'A': // Fast yaw left
            yaw -= 0.1;
            break;
        case 's': // Slow pitch down
            pitch -= 0.01;
            break;
        case 'S': // Fast pitch down
            pitch -= 0.1;
            break;
        case 'd': // Slow yaw right
            yaw += 0.01;
            break;
        case 'D': // Fast yaw right
            yaw += 0.1;
            break;
        case 'j': // Slow zoom out
            radius += 0.01;
            break;
        case 'J': // Fast zoom out
            radius += 0.1;
            break;
        case 'k': // Slow zoom in
            radius -= 0.01;
            break;
        case 'K': // Fast zoom in
            radius -= 0.1;
            break;
        default:
            break;
    }

    if (pitch > M_PI_2)
        pitch = M_PI_2;
    else if (pitch < -M_PI_2)
        pitch = -M_PI_2;
}

void Camera::setPerspective(int w, int h) const
{
    gluPerspective(fov, (float) w / (float) h, near, far);
}

/*
void Camera::setProjection(int w, int h) const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    setPerspective(w, h);
    glMatrixMode(GL_MODELVIEW);
}
*/
