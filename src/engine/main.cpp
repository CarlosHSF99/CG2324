#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include "engine/world.h"
#include "engine/xml_world_loader.h"

using std::cos, std::sin, std::sqrt, std::atan2, std::asin;

void renderScene();

void changeSize(int w, int h);

void processNormalKeys(unsigned char key, int xx, int yy);

void drawAxis();

World world;

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <xml_file>" << std::endl;
        return 1;
    }

    world = XMLWorldLoader::load(argv[1]);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - world.window.width) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - world.window.height) / 2);
    glutInitWindowSize(world.window.width, world.window.height);
    glutCreateWindow(world.window.title);

    // required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);

    // init GLEW
#ifndef __APPLE__
    glewInit();
#endif

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);

    world.group.initBuffers();

    glutMainLoop();

    return 1;
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.camera.place();

    drawAxis();

    world.draw();

    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    // Doesn't seem useful. Might be removed.
    world.window.width = w;
    world.window.height = h;

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
    world.camera.setPerspective(w, h);

    // Get Back to the ModelView
    glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
    world.camera.reactKey(key, xx, yy);

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
