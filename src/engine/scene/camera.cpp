#include <GL/glut.h>
#include <cmath>
#include "deps/tinyxml2.h"
#include "engine/scene/camera.h"

using namespace tinyxml2;

Camera::Camera(const Point3 &position, const Point3 &lookAt, const Vector3 &up, float fov, float near, float far)
        : position(position), lookAt(lookAt), up(up), fov(fov), near(near), far(far)
{
    radius = sqrtf(powf(position.x - lookAt.x, 2) + powf(position.y - lookAt.y, 2) + powf(position.z - lookAt.z, 2));
    pitch = asinf((position.y - lookAt.y) / radius);
    yaw = atan2f(position.x - lookAt.x, position.z - lookAt.z);
}

Camera::Camera(tinyxml2::XMLElement *cameraElement)
{
    XMLElement *positionElement = cameraElement->FirstChildElement("position");
    if (positionElement) {
        position = Point3(positionElement);
    }
    XMLElement *lookAtElement = cameraElement->FirstChildElement("lookAt");
    if (lookAtElement) {
        lookAt = Point3(lookAtElement);
    }
    XMLElement *upElement = cameraElement->FirstChildElement("up");
    if (upElement) {
        up = Vector3(upElement);
    }
    XMLElement *projectionElement = cameraElement->FirstChildElement("projection");
    if (projectionElement) {
        projectionElement->QueryFloatAttribute("fov", &fov);
        projectionElement->QueryFloatAttribute("near", &near);
        projectionElement->QueryFloatAttribute("far", &far);
    }

    radius = sqrtf(powf(position.x - lookAt.x, 2) + powf(position.y - lookAt.y, 2) + powf(position.z - lookAt.z, 2));
    pitch = asinf((position.y - lookAt.y) / radius);
    yaw = atan2f(position.x - lookAt.x, position.z - lookAt.z);
}

void Camera::place()
{
    glLoadIdentity();

    position = {lookAt.x + radius * cosf(pitch) * sinf(yaw),
                lookAt.y + radius * sinf(pitch),
                lookAt.z + radius * cosf(pitch) * cosf(yaw)};

    gluLookAt(position.x, position.y, position.z,
              lookAt.x, lookAt.y, lookAt.z,
              up.x, up.y, up.z);
}

void Camera::reactKey(unsigned char key, int, int)
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

    if (pitch > (M_PI_2 - 0.01)) {
        pitch = M_PI_2 - 0.01;
    } else if (pitch < (-M_PI_2 + 0.01)) {
        pitch = -M_PI_2 + 0.01;
    }
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
