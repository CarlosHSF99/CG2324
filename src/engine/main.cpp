#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include "engine/world.h"
#include "engine/xml_world_loader.h"

using std::cos, std::sin, std::sqrt, std::atan2, std::asin;

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <xml_file>" << std::endl;
        return 1;
    }

    Window window = XMLWorldLoader::loadWindow(argv[1]);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(window.x, window.y);
    glutInitWindowSize(window.width, window.height);
    glutCreateWindow(window.title);

    glewInit();

    static World world = XMLWorldLoader::loadWorld(argv[1]);

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
