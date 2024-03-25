#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <memory>
#include "utils/model.h"
#include "deps/tinyxml2.h"
#include "engine/group.h"

using namespace tinyxml2;

using std::cos, std::sin, std::sqrt, std::atan2, std::asin;

void renderScene();

void changeSize(int w, int h);

void processNormalKeys(unsigned char key, int xx, int yy);

void drawAxis();

float positionX, positionY, positionZ;
float lookAtX, lookAtY, lookAtZ;
float upX, upY, upZ;
float fov, near, far;
float pitch, yaw;
float radius;

std::vector<Group> groups;

Group parseGroup(XMLElement *groupElement)
{
    std::vector<std::unique_ptr<Transform>> transforms;
    std::vector<Model> models;
    std::vector<Group> subgroups;

    XMLElement *transformsElement = groupElement->FirstChildElement("transform");
    if (transformsElement) {
        XMLElement *translateElement = transformsElement->FirstChildElement("translate");
        if (translateElement) {
            float x, y, z;
            translateElement->QueryFloatAttribute("x", &x);
            translateElement->QueryFloatAttribute("y", &y);
            translateElement->QueryFloatAttribute("z", &z);
            transforms.push_back(std::make_unique<Translate>(x, y, z));
        }
        XMLElement *rotateElement = transformsElement->FirstChildElement("rotate");
        if (rotateElement) {
            float angle, x, y, z;
            rotateElement->QueryFloatAttribute("angle", &angle);
            rotateElement->QueryFloatAttribute("x", &x);
            rotateElement->QueryFloatAttribute("y", &y);
            rotateElement->QueryFloatAttribute("z", &z);
            transforms.push_back(std::make_unique<Rotate>(angle, x, y, z));
        }
        XMLElement *scaleElement = transformsElement->FirstChildElement("scale");
        if (scaleElement) {
            float x, y, z;
            scaleElement->QueryFloatAttribute("x", &x);
            scaleElement->QueryFloatAttribute("y", &y);
            scaleElement->QueryFloatAttribute("z", &z);
            transforms.push_back(std::make_unique<Scale>(x, y, z));
        }
    }

    XMLElement *modelsElement = groupElement->FirstChildElement("models");
    if (modelsElement) {
        XMLElement *modelElement = modelsElement->FirstChildElement("model");
        while (modelElement) {
            const char *file = modelElement->Attribute("file");
            models.emplace_back(file);
            modelElement = modelElement->NextSiblingElement("model");
        }
    }

    XMLElement *subgroupElement = groupElement->FirstChildElement("group");
    while (subgroupElement) {
        subgroups.push_back(parseGroup(subgroupElement));
        subgroupElement = subgroupElement->NextSiblingElement("group");
    }

    return {std::move(transforms), std::move(models), std::move(subgroups)};
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <xml_file>" << std::endl;
        return 1;
    }

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

            while (groupElement) {
                groups.push_back(parseGroup(groupElement));
                groupElement = groupElement->NextSiblingElement("group");
            }
        }
    } else {
        std::cerr << "Failed to load file." << std::endl;
    }

    radius = (float) sqrt(pow(positionX - lookAtX, 2) + pow(positionY - lookAtY, 2) + pow(positionZ - lookAtZ, 2));
    pitch = asin((positionY - lookAtY) / radius);
    yaw = atan2((positionX - lookAtX), (positionZ - lookAtZ));

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
    glutInitWindowSize(width, height);
    glutCreateWindow(argv[1]);

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

    drawAxis();

    for (const auto &group: groups) {
        group.draw();
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
        case 27: // Quit - ESC Key
            exit(0);
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

    glutPostRedisplay();
}

void drawAxis()
{
    // save current color
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);

    glBegin(GL_LINES);
    // X Axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    // restore previous color
    glColor4fv(currentColor);
}
