#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "utils/model.h"
#include "deps/tinyxml2.h"

using namespace tinyxml2;

using std::cos, std::sin, std::sqrt, std::atan2, std::asin;

void renderScene();

void changeSize(int w, int h);

void processNormalKeys(unsigned char key, int xx, int yy);

float positionX, positionY, positionZ;
float lookAtX, lookAtY, lookAtZ;
float upX, upY, upZ;
float fov, near, far;
float pitch, yaw;
float radius;
std::vector<Model> models;

int main(int argc, char **argv)
{
    int width, height;

    XMLDocument doc;
    if (doc.LoadFile(argv[1]) == XML_SUCCESS) {
        XMLElement *worldElement = doc.FirstChildElement("world");
        if (worldElement) {
            XMLElement *windowElement = worldElement->FirstChildElement("window");
            if (windowElement) {
                windowElement->QueryIntAttribute("width", &width);
                windowElement->QueryIntAttribute("height", &height);
            }

            XMLElement *cameraElement = worldElement->FirstChildElement("camera");
            if (cameraElement) {
                XMLElement *positionElement = cameraElement->FirstChildElement("position");
                if (positionElement) {
                    positionElement->QueryFloatAttribute("x", &positionX);
                    positionElement->QueryFloatAttribute("y", &positionY);
                    positionElement->QueryFloatAttribute("z", &positionZ);
                }
                XMLElement *lookAtElement = cameraElement->FirstChildElement("lookAt");
                if (lookAtElement) {
                    lookAtElement->QueryFloatAttribute("x", &lookAtX);
                    lookAtElement->QueryFloatAttribute("y", &lookAtY);
                    lookAtElement->QueryFloatAttribute("z", &lookAtZ);
                }
                XMLElement *upElement = cameraElement->FirstChildElement("up");
                if (upElement) {
                    upElement->QueryFloatAttribute("x", &upX);
                    upElement->QueryFloatAttribute("y", &upY);
                    upElement->QueryFloatAttribute("z", &upZ);
                }
                XMLElement *projectionElement = cameraElement->FirstChildElement("projection");
                if (projectionElement) {
                    projectionElement->QueryFloatAttribute("fov", &fov);
                    projectionElement->QueryFloatAttribute("near", &near);
                    projectionElement->QueryFloatAttribute("far", &far);
                }
            }

            XMLElement *groupElement = worldElement->FirstChildElement("group");
            if (groupElement) {
                XMLElement *modelsElement = groupElement->FirstChildElement("models");
                if (modelsElement) {
                    XMLElement *modelElement = modelsElement->FirstChildElement("model");
                    while (modelElement) {
                        const char *file = modelElement->Attribute("file");
                        models.emplace_back(file);
                        modelElement = modelElement->NextSiblingElement("model");
                    }
                }
            }
        }
    } else {
        std::cerr << "Failed to load file." << std::endl;
    }

    radius = (float) sqrt(pow(positionX - lookAtX, 2) + pow(positionY - lookAtY, 2) + pow(positionZ - lookAtZ, 2));
    pitch = asin((positionY - lookAtY) / radius);
    yaw = atan2((positionZ - lookAtZ), (positionX - lookAtX));

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG@DI-UM");

    // required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glutMainLoop();

    return 1;
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    positionX = radius * cos(pitch) * sin(yaw);
    positionY = radius * sin(pitch);
    positionZ = radius * cos(pitch) * cos(yaw);

    gluLookAt(positionX, positionY, positionZ,
              lookAtX, lookAtY, lookAtZ,
              upX, upY, upZ);

    for (const auto &model: models) {
        model.draw();
    }

    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you can't make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = (float) w / (float) h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(fov, ratio, near, far);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
    switch (key) {
        case 27:
            exit(0);
        case 'w':
            pitch += 0.01;
            break;
        case 'W':
            pitch += 0.1;
            break;
        case 'a':
            yaw -= 0.01;
            break;
        case 'A':
            yaw -= 0.1;
            break;
        case 's':
            pitch -= 0.01;
            break;
        case 'S':
            pitch -= 0.1;
            break;
        case 'd':
            yaw += 0.01;
            break;
        case 'D':
            yaw += 0.1;
            break;
        case 'j':
            radius += 0.01;
            break;
        case 'J':
            radius += 0.1;
            break;
        case 'k':
            radius -= 0.01;
            break;
        case 'K':
            radius -= 0.1;
            break;
        default:
            break;
    }

    if (pitch > M_PI_2)
        pitch = M_PI_2;
    else if (pitch < -M_PI_2)
        pitch = -M_PI_2;

    glutPostRedisplay();
}
