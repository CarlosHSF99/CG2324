#include <iostream>
#include <GL/glut.h>
#include <fstream>
#include <cmath>
#include "utils/model.h"

using std::cout, std::endl, std::ifstream;

void renderScene();
void changeSize(int w, int h);

int main(int argc, char **argv)
{
    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

    // required callback registry
	glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glutMainLoop();

    return 1;
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(10.0, 10.0, 10.0,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    Model plane("plane.3d");
    plane.draw();

    glutSwapBuffers();
}

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you can't make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = 1.0 * w / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45, ratio, 1, 1000);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}