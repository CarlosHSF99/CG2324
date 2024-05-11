#include <map>
#include <iostream>
#include "deps/tinyxml2.h"
#include "engine/world.h"

using namespace tinyxml2;

void drawAxis();

World::World(XMLElement *worldElement)
{
    XMLElement *cameraElement = worldElement->FirstChildElement("camera");
    if (cameraElement) {
        camera = Camera(cameraElement);
    }
    XMLElement *groupElement = worldElement->FirstChildElement("group");
    if (groupElement) {
        group = Group(groupElement);
    }
}

void World::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.place();

    drawAxis();

    group.draw((float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f);

    glutSwapBuffers();
}

void World::changeSize(int w, int h) const
{
    // Prevent a divide by zero, when window is too short
    // (you can't make a window of zero width).
    if (h == 0)
        h = 1;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    camera.setPerspective(w, h);

    // Get Back to the ModelView
    glMatrixMode(GL_MODELVIEW);
}

void World::processNormalKeys(unsigned char key, int xx, int yy)
{
    camera.reactKey(key, xx, yy);

    switch (key) {
        case 27: // Quit - ESC Key
            exit(0);
        default:
            break;
    }

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
