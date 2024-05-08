#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "engine/window.h"
#include "engine/world.h"
#include "deps/tinyxml2.h"

using namespace tinyxml2;

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <xml_file>" << std::endl;
        return 1;
    }

    XMLDocument doc;
    if (doc.LoadFile(argv[1]) != XML_SUCCESS) {
        std::cerr << "Failed to load file." << std::endl;
        return 1;
    }

    XMLElement *worldElement = doc.FirstChildElement("world");
    if (!worldElement) {
        return 1;
    }

    Window window(worldElement->FirstChildElement("window"));

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(window.x, window.y);
    glutInitWindowSize(window.width, window.height);
    glutCreateWindow(argv[1]);

    glewInit();

    static World world(worldElement);

    // callback registry
    glutDisplayFunc([]() -> void { world.renderScene(); });
    glutReshapeFunc([](int w, int h) -> void { world.changeSize(w, h); });
    glutIdleFunc([]() -> void { world.renderScene(); });
    glutKeyboardFunc([](unsigned char key, int xx, int yy) -> void { world.processNormalKeys(key, xx, yy); });

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glutMainLoop();

    return 1;
}
